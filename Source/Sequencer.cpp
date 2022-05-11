/*
  ==============================================================================

    Sequencer.cpp
    Created: 11 May 2022 2:47:54pm
    Author:  Damien

  ==============================================================================
*/

#include "Sequencer.h"

Sequencer::Sequencer(juce::AudioProcessorValueTreeState& parameters) :
    sequencerModules(4,SequencerModule(parameters))
{
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

    
    // If sequencer module not currently playing, modu.initialise it

    for (auto&& modu : sequencerModules) modu.generateMidi(buffer, playhead);
}
