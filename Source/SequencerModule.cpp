/*
  ==============================================================================

    SequencerModule.cpp
    Created: 11 May 2022 2:49:33pm
    Author:  Damien

  ==============================================================================
*/

#include "SequencerModule.h"

SequencerModule::SequencerModule(juce::AudioProcessorValueTreeState& parameters)
{
}

SequencerModule::~SequencerModule()
{
}

void SequencerModule::initialise(double s, int b)
{
    sampleRate = s;
    bufferSize = b;
}

void SequencerModule::resetRhythmTrack()
{
    midiController.initialise(sampleRate, bufferSize);
}

void SequencerModule::generateMidi(juce::MidiBuffer& buffer, juce::AudioPlayHead::CurrentPositionInfo& playhead)
{

}
