/*
  ==============================================================================

    Sequencer.cpp
    Created: 11 May 2022 2:47:54pm
    Author:  Damien

  ==============================================================================
*/

#include "Sequencer.h"

Sequencer::Sequencer(juce::AudioProcessorValueTreeState& parameters) :
    sequencerModules(4,SequencerModule(parameters)), 
    gen(rd()),
    randomSelect({ 0, 1, 2, 3})
{
    modeSelect = parameters.getRawParameterValue("modeSelect");
    for (auto&& entry : midiNoteToSequencerMap)
    {
        entry = &sequencerModules[0];
    }
}

Sequencer::~Sequencer()
{
}

void Sequencer::initialise(double sampleRate, int bufferSize)
{
    for (auto&& modu : sequencerModules) modu.initialise(sampleRate, bufferSize);
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
    // sustain -> manually add notes to an array - these are notes currently held down??
    //for (auto&& modu : sequencerModules) modu.generateMidi(buffer, playhead);

    buffer.clear();
    for (auto&& message : incomingMidi) processMidi(message.first, message.second);

    for (auto&& modu : sequencerModules) modu.generateMidi(buffer, playhead);
}

void Sequencer::processMidi(juce::MidiMessage message, int sampleLocation)
{
    // Each sequencer needs multiple voices!!

    // Sequencer >> SequencerModule >> MidiVoice >> MidiController
    //                              >> Rhythm >> Beat
    // Pass midi voice + buffer to rhythm and beat,  beat will make checks and pass buffer to voice

    if (message.isNoteOn())
    {
        // note off any module currently running from this note
        // run algorithm from mode selection (eg. random module selection)
        // assign note on to module

        if (midiState.isNoteOn(0, message.getNoteNumber())) midiNoteToSequencerMap[message.getNoteNumber()]->addNoteOff(message, sampleLocation);
        midiState.processNextMidiEvent(message);

        // Mode selection
        if (modeSelect->load() == 0) processRandomNoteOn(message, sampleLocation); // Mode 1
    }
    else if (message.isNoteOff())
    {
        midiState.processNextMidiEvent(message);
        midiNoteToSequencerMap[message.getNoteNumber()]->addNoteOff(message, sampleLocation);
    }
    else if (message.isSustainPedalOn())
    {
        // add sustain flag to all current voices
        for (auto&& modu : sequencerModules) modu.changeSustain(true,sampleLocation);
    }
    else if (message.isSustainPedalOff())
    {
        // stop all voices playing that aren't currently on in midiState
        for (int midiNote = 0; midiNote < 128; midiNote++)
        {
            if (!midiState.isNoteOn(0, midiNote)) midiNoteToSequencerMap[midiNote]->removeSustainedNote(midiNote, sampleLocation);
            else midiNoteToSequencerMap[midiNote]->changeSustain(false, sampleLocation);
        }
    }
}

void Sequencer::processRandomNoteOn(juce::MidiMessage message, int sampleLocation)
{
    auto selection = randomSelect(gen);
    sequencerModules[selection].addNoteOn(message,sampleLocation);
    midiNoteToSequencerMap[message.getNoteNumber()] = &sequencerModules[selection];
}
