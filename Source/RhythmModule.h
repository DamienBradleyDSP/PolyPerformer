/*
  ==============================================================================

    RhythmModule.h
    Created: 11 May 2022 2:49:42pm
    Author:  Damien

  ==============================================================================
*/

#pragma once

#pragma once
#include "JuceHeader.h"
#include "ProjectSettings.h"
#include "MidiVoice.h"
#include "Beat.h"

// Rhythm module is accessed in a tracked cycle, freeform based on the sample locaiton and distance from last point
// could be rounding errors so sample accuracy needed with INT64 in currentposition playhead

class RhythmModule
{
public:
    RhythmModule() = delete;
    RhythmModule(juce::AudioProcessorValueTreeState& parameters, int rhythmNumber);
    ~RhythmModule();

    void generateMidi(std::list<MidiVoice*>& voices);
    void getNumberOfBars(bars& runningBarTotal);

    const int rhythmNumber;

private:
    bars calculateBarSpan();

    std::vector<Beat> beats;

    bars lastModuleBarEnding = 0;

    // GUI Params
    std::atomic<float>* moduleOnState;
    std::atomic<float>* numberOfBeats;
    std::atomic<float>* numberOfBars;
    std::atomic<float>* selectedBeats;
};