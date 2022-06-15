/*
  ==============================================================================

    Sequencer.cpp
    Created: 11 May 2022 2:47:54pm
    Author:  Damien

  ==============================================================================
*/

#include "Sequencer.h"

Sequencer::Sequencer(juce::AudioProcessorValueTreeState& parameters) :
    gen(rd()),
    randomSelect(0.0f, 1.0f)
{
    for (int moduleNumber = 0; moduleNumber < ProjectSettings::numberOfModules; moduleNumber++)
    {
        sequencerModules.push_back(std::unique_ptr<SequencerModule>(new SequencerModule(parameters, moduleNumber)));
        moduleOnOff.push_back(parameters.getRawParameterValue("moduleOnOff" + juce::String(moduleNumber)));
        moduleNoteNumber.push_back(parameters.getRawParameterValue("moduleNoteNumber" + juce::String(moduleNumber)));
    }

    modeSelect = parameters.getRawParameterValue("modeSelect");
    for (int midiNote=1; midiNote <= 127 ; midiNote++)
    {
        midiNoteToSequencerMap.insert(std::make_pair(midiNote, sequencerModules[0].get()));
    }
    
}

Sequencer::~Sequencer()
{
}

void Sequencer::initialise(double s, int b)
{
    for (auto&& modu : sequencerModules) modu->initialise(s, b);

    sampleRate = s;
    bufferSize = b;
}

void Sequencer::generateMidi(juce::MidiBuffer& buffer, juce::AudioPlayHead::CurrentPositionInfo& playhead)
{
   // Each sequencer module needs its own midi controller - this controller will assess time based on the start
   // of the midi note // another starting location as given by the mode select function


    /*
    MODES:

    Hanging mode: Rhythm stays fixed at the end [ TOGGLE ON/OFF ALL RHYTHMS?]
    Quantise mode: Rhythms quantise the midi to the timeline [Toggle ON/OFF all rhythms]

    M1: Random rhythm selection

    M2: Automatic sequential selection mode

    M3: Left hand key selection mode - selecting in the left hand will play the desired rhythms in automatic sequential
    IE: Left plays R1, all notes play R1 - this sticks until another note selected
    Left plays R1-R2, all notes automatic sequence rhythms 1 & 2

    M4: 
    */

    // If sequencer module not currently playing, modu.initialise it // reset the internal sample count
    // We need to listen to the sustain pedal, this is important to establish
    // Assess the mode and current buffer only based on incoming midi messages and current mode selected
    std::list<std::pair<MidiMessage,samples>> incomingMidi;
    MidiMessage nullMessage;
    MidiBuffer::Iterator i(buffer);
    int sampleLocation;
    while (i.getNextEvent(nullMessage, sampleLocation)) incomingMidi.push_back(std::make_pair(nullMessage, sampleLocation));
    buffer.clear();    

    for (auto&& message : incomingMidi) processIncomingMidi(message.first, message.second);
    for(auto&& modu : sequencerModules) modu->generateMidi(buffer, playhead);

    sampleSinceLastNote += bufferSize;
}

void Sequencer::replaceModuleState(std::unordered_map<juce::String, float>& moduleState, int moduleNumber)
{
    sequencerModules[moduleNumber]->replaceModuleState(moduleState);
}

void Sequencer::processIncomingMidi(juce::MidiMessage message, int sampleLocation)
{
    // Each sequencer needs multiple voices!!

    // Sequencer >> SequencerModule >> MidiVoice >> MidiController
    //                              >> Rhythm >> Beat
    // Pass midi voice + buffer to rhythm and beat,  beat will make checks and pass buffer to voice

    message.setTimeStamp(sampleLocation);
    

    // if sustain pedal on/off, send to all
    if (message.isSustainPedalOff() || message.isSustainPedalOn())
    {
        for (auto&& modu : sequencerModules) modu->addMessage(message);
        return;
    }

    // if midi note matches given notes in selectors, process as performer midi
    auto iter = sequencerModules.begin();
    for (auto&& moduleNote : moduleNoteNumber)
    {
        if (message.getNoteNumber() == moduleNote->load())
        {
            processPerformerMidi(message);
            return;
        }
        std::advance(iter, 1);
    }
    
    // if note off, send to given midi to sequencer map
     
    if (message.isNoteOff())
    {
        if (!midiNoteToSequencerMap[message.getNoteNumber()]) return;
        else
        {
            midiNoteToSequencerMap[message.getNoteNumber()]->addMessage(message);
        }
    }
    else if (message.isNoteOn())
    {
        if(modeSelect->load()==1) noteOnModeRandomSelection(message);
        else if(modeSelect->load()==2) noteOnModeSequentialSelection(message);
        else if(modeSelect->load()==3) noteOnModeTimeLinkedRandom(message);
        else if(modeSelect->load()==4) noteOnModeChordLinkedSequential(message);
    }
}

void Sequencer::forceNoteOff(juce::MidiMessage message)
{
    auto noteOffMessage = message;
    noteOffMessage.setTimeStamp(0);
    if (midiNoteToSequencerMap[message.getNoteNumber()])
    {
        midiNoteToSequencerMap[message.getNoteNumber()]->forceVoiceOff(noteOffMessage);
        midiNoteToSequencerMap[message.getNoteNumber()] = nullptr;
    }
}

void Sequencer::processPerformerMidi(juce::MidiMessage message)
{

    performerMidiKeyState.processNextMidiEvent(message);

    // verify key state still represents corrects performer here
    auto module1 = performerMidiKeyState.isNoteOnForChannels(127, moduleNoteNumber[0]->load());
    auto module2 = performerMidiKeyState.isNoteOnForChannels(127, moduleNoteNumber[1]->load());
    auto module3 = performerMidiKeyState.isNoteOnForChannels(127, moduleNoteNumber[2]->load());
    auto module4 = performerMidiKeyState.isNoteOnForChannels(127, moduleNoteNumber[3]->load());

    performerMidiEngagedModules.clear();
    if (module1) performerMidiEngagedModules.push_back(sequencerModules[0].get());
    if (module2) performerMidiEngagedModules.push_back(sequencerModules[1].get());
    if (module3) performerMidiEngagedModules.push_back(sequencerModules[2].get());
    if (module4) performerMidiEngagedModules.push_back(sequencerModules[3].get());
}

void Sequencer::noteOnModeRandomSelection(juce::MidiMessage message)
{
    // Random note selection, if performer notes held down it will only select from those modules, forces note off before playing
    
    forceNoteOff(message);

    std::vector<SequencerModule*> enabledModules;

    for (auto&& modu : performerMidiEngagedModules)
    {
        if (modu->isModuleEnabled()) enabledModules.push_back(modu);
    }
    if (enabledModules.size() == 0) for (auto&& modu : sequencerModules)
    {
        if (modu->isModuleEnabled()) enabledModules.push_back(modu.get());
    }


    auto selection = randomSelect(gen);
    int size = enabledModules.size();
    if (size == 0) return;
    float scaledSelection = std::round(selection * (size - 1));

    enabledModules[(int)scaledSelection]->addMessage(message);
    midiNoteToSequencerMap[message.getNoteNumber()] = enabledModules[(int)scaledSelection];
}

void Sequencer::noteOnModeSequentialSelection(juce::MidiMessage message)
{
    // Sequential note selection, if performer notes held down it will only select from those modules, forces note off before playing

    forceNoteOff(message);

    std::vector<SequencerModule*> enabledModules;

    for (auto&& modu : performerMidiEngagedModules)
    {
        if (modu->isModuleEnabled()) enabledModules.push_back(modu);
    }
    if (enabledModules.size() == 0) for (auto&& modu : sequencerModules)
    {
        if (modu->isModuleEnabled()) enabledModules.push_back(modu.get());
    }

    int size = enabledModules.size();
    if (size == 0) return;

    if (nextSequentialSelection >= size) nextSequentialSelection = 0;
    enabledModules[nextSequentialSelection]->addMessage(message);
    midiNoteToSequencerMap[message.getNoteNumber()] = enabledModules[nextSequentialSelection];

    nextSequentialSelection++;
}

void Sequencer::noteOnModeTimeLinkedRandom(juce::MidiMessage message)
{
    auto samplesBetweenChanges = ProjectSettings::numberOfSecondsBetweenRhythmChange * sampleRate;

    if (sampleSinceLastNote < samplesBetweenChanges && currentSelection) if(currentSelection->isModuleEnabled())
    {
        forceNoteOff(message);
        currentSelection->addMessage(message);
        midiNoteToSequencerMap[message.getNoteNumber()] = currentSelection;
        sampleSinceLastNote = 0;
        return;
    }

    sampleSinceLastNote = 0;

    forceNoteOff(message);

    std::vector<SequencerModule*> enabledModules;

    for (auto&& modu : performerMidiEngagedModules)
    {
        if (modu->isModuleEnabled()) enabledModules.push_back(modu);
    }
    if (enabledModules.size() == 0) for (auto&& modu : sequencerModules)
    {
        if (modu->isModuleEnabled()) enabledModules.push_back(modu.get());
    }

    auto selection = randomSelect(gen);
    int size = enabledModules.size();
    if (size == 0) return;
    float scaledSelection = std::round(selection * (size - 1));

    enabledModules[(int)scaledSelection]->addMessage(message);
    midiNoteToSequencerMap[message.getNoteNumber()] = enabledModules[(int)scaledSelection];
    currentSelection = enabledModules[(int)scaledSelection];

}

void Sequencer::noteOnModeChordLinkedSequential(juce::MidiMessage message)
{
    // Unused currently
    noteOnModeRandomSelection(message);
}
