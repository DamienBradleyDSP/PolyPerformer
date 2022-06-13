/*
  ==============================================================================

    Sequencer.h
    Created: 11 May 2022 2:47:54pm
    Author:  Damien

  ==============================================================================
*/

#pragma once
#include <random>
#include <unordered_map>
#include <unordered_set>
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

    void replaceModuleState(std::unordered_map<juce::String, float>& moduleState, int moduleNumber);

private:
    void processIncomingMidi(juce::MidiMessage message, int sampleLocation);
    void forceNoteOff(juce::MidiMessage message);
    void processPerformerMidi(juce::MidiMessage message);
    void processRandomNoteOn(juce::MidiMessage message);

    std::vector<std::unique_ptr<SequencerModule>> sequencerModules; // the four sequencer modules allowed to be used
    std::unordered_map<int, SequencerModule*> midiNoteToSequencerMap; // maps 128 midi notes to the sequencer using that note VIA pointer
    MidiKeyboardState performerMidiKeyState; // key state for the selected notes that govern the sequencer modules ONLY

    // Noise generator for mode 1
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<float> randomSelect;

    std::atomic<float>* modeSelect;
    std::vector<std::atomic<float>*> moduleOnOff;
    std::vector<std::atomic<float>*> moduleNoteNumber;
};