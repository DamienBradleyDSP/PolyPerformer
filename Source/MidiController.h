/*
  ==============================================================================

    MidiController.h
    Created: 11 May 2022 2:48:26pm
    Author:  Damien

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "ProjectSettings.h"

class MidiController
{
public:
    MidiController() = delete;
    MidiController(juce::AudioProcessorValueTreeState& parameters);
    ~MidiController();

    // SequencerModule Interface
    void initialise(double sampleRate, int bufferSize);
    void resetRhythmTrack(int sampleLocation);
    void calculateBufferSamples(juce::AudioPlayHead::CurrentPositionInfo& currentpositionstruct, bars totalNumberOfBars);
    void applyMidiMessages(juce::MidiBuffer& buffer);

    // Beat Interface
    void addMidiMessage(juce::MidiMessage const& noteOnMessage, bars noteOnPosition, juce::MidiMessage const& noteOffMessage, bars noteOffPosition, bool sustain = false);


private:

    void checkNoteOffMessages();
    int getLocation(bars barPosition);

    double sampleRate;
    int bufferLength;
    samples samplesFromRhythmStart;
    bars totalNumberOfBars;
    samples oneBarSampleLength;
    samples totalSampleLength;

    std::pair<juce::int64, juce::int64> bufferSpan;
    std::pair<samples, samples> sampleSpan;
    std::pair<samples, samples> sampleSpanOverspill;
    bool sampleOverspill = false;

    std::list<std::pair<juce::MidiMessage, samples>> bufferMidiMessages;
    std::list<std::pair<juce::MidiMessage, bars>> noteOffMessages;
    std::list<juce::MidiMessage> sustainedMidiMessages;

    bool sustainToNextNote = false;

    bool resetNoteStart = false;
    int samplesToNoteReset = 0;
};