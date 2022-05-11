/*
  ==============================================================================

    Sequencer.h
    Created: 11 May 2022 2:47:54pm
    Author:  Damien

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "SequencerModule.h"

class Sequencer
{
public:
    Sequencer()=delete;
    Sequencer(juce::AudioProcessorValueTreeState& parameters);
    ~Sequencer();

    void initialise(double sampleRate, int bufferSize);
    void generateMidi(juce::MidiBuffer& buffer, juce::AudioPlayHead::CurrentPositionInfo& playhead);

private:
    std::list<SequencerModule> sequencerModules;
};