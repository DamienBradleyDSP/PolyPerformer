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

    void addNoteOn(juce::MidiMessage message, int sampleLocation);
    void addNoteOff(juce::MidiMessage message, int sampleLocation);
    void changeSustain(bool sustain, int sampleLocation);
    void removeSustainedNote(int noteNumber, int sampleLocation);

private:
    
    std::vector<MidiVoice> midiVoices;
    std::list<MidiVoice*> playingVoices; // holds playing voices in order
    std::queue<MidiVoice*> nonPlayingVoices; // holds non-playing voices

    std::vector<RhythmModule> rhythmModules;

    bars barOffset = 0;
};