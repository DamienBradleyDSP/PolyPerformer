/*
  ==============================================================================

    SequencerModule.h
    Created: 11 May 2022 2:49:33pm
    Author:  Damien

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "ProjectSettings.h"
#include "MidiController.h"
#include "MidiVoice.h"
#include "RhythmModule.h"

class SequencerModule
{
public:
    SequencerModule() = delete;
    SequencerModule(juce::AudioProcessorValueTreeState& parameters);
    ~SequencerModule();

    void initialise(double sampleRate, int bufferSize);
    void generateMidi(juce::MidiBuffer& buffer, juce::AudioPlayHead::CurrentPositionInfo& playhead);

    void addNoteOn(juce::MidiMessage message);
    void addNoteOff(juce::MidiMessage message);
    void changeSustain(juce::MidiMessage message);

private:

    std::vector<std::unique_ptr<MidiVoice>> midiVoices;
    std::list<MidiVoice*> playingVoices; // holds playing voices in order
    std::queue<MidiVoice*> nonPlayingVoices; // holds non-playing voices
    std::array<MidiVoice*, 128> midiNoteToSequencerMap;

    std::vector<std::unique_ptr<RhythmModule>> rhythmModules;

    bars barOffset = 0;
};