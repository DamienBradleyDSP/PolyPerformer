/*
  ==============================================================================

    Beat.h
    Created: 25 Oct 2021 3:55:25pm
    Author:  Damien

  ==============================================================================
*/

#pragma once
#include <unordered_map>
#include "JuceHeader.h"
#include "ProjectSettings.h"
#include "MidiVoice.h"

class Beat
{
public:
    Beat() = delete;
    Beat(juce::AudioProcessorValueTreeState& parameters, int rhythmNumber, int beatNumber);
    ~Beat();

    void setBarPositionLength(bars barPosition, bars length);
    void applyMidiMessages(std::list<MidiVoice*>& midiVoices, bars lastModuleBarEnding);

    void replaceModuleState(std::unordered_map<juce::String, float>& newState);
private:

    const int rhythmNumber; // 
    const int beatNumber;

    bars beatPosition = 0; // beatPosition - integers are bars and fractional amounts are positions within the bar
    bars beatLength = 0;

    juce::MidiMessage noteOn;
    juce::MidiMessage noteOff;
    juce::MidiMessage allNotesOff;

    // User params
    std::atomic<float> onState;
    std::atomic<float> velocity;
    std::atomic<float> noteLength;
    int midiNote = ProjectSettings::midiNote;
    std::atomic<float> midiSemitone;
    std::atomic<float> midiOctave;
    std::atomic<float> sustain;
};