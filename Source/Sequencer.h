/*
  ==============================================================================

    Sequencer.h
    Created: 11 May 2022 2:47:54pm
    Author:  Damien

  ==============================================================================
*/

#pragma once
#include <random>
#include "JuceHeader.h"
#include "SequencerModule.h"
#include "ProjectSettings.h"

class Sequencer
{
public:
    Sequencer()=delete;
    Sequencer(juce::AudioProcessorValueTreeState& parameters);
    ~Sequencer();

    void initialise(double sampleRate, int bufferSize);
    void generateMidi(juce::MidiBuffer& buffer, juce::AudioPlayHead::CurrentPositionInfo& playhead);

private:
    void processMidi(juce::MidiMessage message, int sampleLocation);
    void processRandomNoteOn(juce::MidiMessage message);

    std::vector<SequencerModule> sequencerModules; // the four sequencer modules allowed to be used
    std::array<SequencerModule*,128> midiNoteToSequencerMap; // maps 128 midi notes to the sequencer using that note VIA pointer
    MidiKeyboardState midiState; // current key state (no sustain pedal included in this class)

    // Noise generator for mode 1
    std::random_device rd;
    std::mt19937 gen;
    std::discrete_distribution<> randomSelect;

    std::atomic<float>* modeSelect;
};