/*
  ==============================================================================

    MidiController.h
    Created: 24 Oct 2021 4:19:29pm
    Author:  Damien

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "ProjectSettings.h"

// This handles the buffer portion of maths, that is to say, the sample locations fall within a particular buffer length
// the rest of the sequencer should have no knowledge of the buffer, only specific sample locations

// The sample location will be calculated and then each will be checked every buffer
// if the sample location is within the buffer, the midimessage is loaded and a new sample location is calculated for that beat

class MidiController
{
public:
    MidiController();
    ~MidiController();

    // Sequencer Interface
    void initialise(double sampleRate, int bufferSize);
    void calculateBufferSamples(juce::AudioPlayHead::CurrentPositionInfo& currentpositionstruct, bars totalNumberOfBars);
    void applyMidiMessages(juce::MidiBuffer& buffer);

    // Beat Interface
    void addMidiMessage(juce::MidiMessage const& noteOnMessage, bars noteOnPosition, juce::MidiMessage const& noteOffMessage, bars noteOffPosition, bool sustain = false);
    //virtual void modifyMessage(juce::MidiMessage& message, int sampleLocation) = 0;

    void resetLoop(int sampleLocation);


private:

    void checkNoteOffMessages();
    int getLocation(bars barPosition);

    std::shared_ptr<juce::AudioProcessorValueTreeState> params;
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

    bool reset = false;
    int resetLocation=0;
};