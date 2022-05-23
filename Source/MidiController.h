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

    // MidiVoice Interface
    void initialise(double sampleRate, int bufferSize);
    void controllerTurningOn(MidiMessage message);
    void controllerTurningOff(MidiMessage message);
    void calculateBufferSamples(juce::AudioPlayHead::CurrentPositionInfo& currentpositionstruct, bars totalNumberOfBars);
    void applyMidiMessages(juce::MidiBuffer& buffer);
    void copyMidiList(MidiController* controllerToCopy);

    // Beat Interface
    void addMidiMessage(juce::MidiMessage& noteOnMessage, bars noteOnPosition, juce::MidiMessage& noteOffMessage, bars noteOffPosition, bool sustain = false);

    // MidiController Interface
    void getDelayedMessages(std::list<std::pair<juce::MidiMessage, bars>>& noteOffMessages,
                            std::list<juce::MidiMessage>& sustainedMidiMessages);

private:

    // MESSAGE / RHYTHM RESET TRACK
    bool resetNoteStart = false;
    bool turningOn = false;
    bool turningOff = false;
    int samplesToNoteReset = 0;
    MidiMessage message;
    void applyMessageChanges(juce::MidiMessage& message);
    //___________________________

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
};