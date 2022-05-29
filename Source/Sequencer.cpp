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
    randomSelect({ 0, 1, 2, 3})
{
    sequencerModules.push_back(std::unique_ptr<SequencerModule>(new SequencerModule(parameters)));
    sequencerModules.push_back(std::unique_ptr<SequencerModule>(new SequencerModule(parameters)));
    sequencerModules.push_back(std::unique_ptr<SequencerModule>(new SequencerModule(parameters)));
    sequencerModules.push_back(std::unique_ptr<SequencerModule>(new SequencerModule(parameters)));


    modeSelect = parameters.getRawParameterValue("modeSelect");
    for (auto&& entry : midiNoteToSequencerMap)
    {
        entry = sequencerModules[0].get();
    }
}

Sequencer::~Sequencer()
{
}

void Sequencer::initialise(double sampleRate, int bufferSize)
{
    for (auto&& modu : sequencerModules) modu->initialise(sampleRate, bufferSize);
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
    sequencerModules[0]->generateMidi(buffer, playhead);
}

void Sequencer::processIncomingMidi(juce::MidiMessage message, int sampleLocation)
{
    // Each sequencer needs multiple voices!!

    // Sequencer >> SequencerModule >> MidiVoice >> MidiController
    //                              >> Rhythm >> Beat
    // Pass midi voice + buffer to rhythm and beat,  beat will make checks and pass buffer to voice

    message.setTimeStamp(sampleLocation);
    sequencerModules[0]->addMessage(message);
}

void Sequencer::processRandomNoteOn(juce::MidiMessage message)
{
    //auto selection = randomSelect(gen);
    //sequencerModules[0]->addNoteOn(message);
    //midiNoteToSequencerMap[message.getNoteNumber()] = sequencerModules[0].get();
}
