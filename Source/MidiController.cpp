/*
  ==============================================================================

    MidiController.cpp
    Created: 11 May 2022 2:48:26pm
    Author:  Damien

  ==============================================================================
*/

#include "MidiController.h"

MidiController::MidiController(juce::AudioProcessorValueTreeState& parameters)
{
}

MidiController::~MidiController()
{
}

void MidiController::initialise(double s, int b)
{
    sampleRate = s;
    bufferLength = b;
    samplesFromRhythmStart = 0;
    sampleSpanOverspill.first = -1;
    sampleSpanOverspill.second = -1;
    bufferSpan.first = 0;
    bufferSpan.second = bufferLength;
    totalNumberOfBars = 0;
    totalSampleLength = 0;
    sampleOverspill = false;
    resetNoteStart = false;
}

void MidiController::resetRhythmTrack(int sampleLocation)
{
    resetNoteStart = true;
    samplesToNoteReset = sampleLocation;
}

void MidiController::calculateBufferSamples(juce::AudioPlayHead::CurrentPositionInfo& currentpositionstruct, bars totalNumOfBars)
{

    totalNumberOfBars = totalNumOfBars;
    double barsPerMinute = (double)currentpositionstruct.bpm / 4.0;
    oneBarSampleLength = ((4.0 * 60.0) / (double)currentpositionstruct.bpm) * sampleRate;
    totalSampleLength = (totalNumberOfBars / barsPerMinute) * 60.0 * sampleRate; //length in samples of the total number of bars spanned by the given rhythm modules

    /// RESET LOOP ADDITION
    if (resetNoteStart)
    {  
        samplesFromRhythmStart = totalSampleLength - samplesToNoteReset;
        resetNoteStart=false;
    }
    /// _____________________________________________

    if ((samplesFromRhythmStart + (double)bufferLength) > totalSampleLength)
    {
        sampleSpan.first = samplesFromRhythmStart;
        sampleSpan.second = totalSampleLength;
        sampleSpanOverspill.first = 0;
        sampleSpanOverspill.second = samplesFromRhythmStart + bufferLength - totalSampleLength;
        sampleOverspill = true;

        samplesFromRhythmStart = 0 + sampleSpanOverspill.second;
    }
    else
    {
        sampleSpan.first = samplesFromRhythmStart;
        sampleSpan.second = samplesFromRhythmStart + bufferLength;
        sampleSpanOverspill.first = -1;
        sampleSpanOverspill.second = -1;
        sampleOverspill = false;
        samplesFromRhythmStart += bufferLength;
    }
    // Bar location at start of buffer
    //return (sampleSpan.first / totalSampleLength) * totalNumberOfBars;
}

void MidiController::applyMidiMessages(juce::MidiBuffer& buffer)
{
    checkNoteOffMessages();

    for (auto&& message : bufferMidiMessages)
    {
        buffer.addEvent(message.first, message.second);
    }
    bufferMidiMessages.clear();
}

void MidiController::addMidiMessage(juce::MidiMessage const& noteOnMessage, bars noteOnPosition, juce::MidiMessage const& noteOffMessage, bars noteOffPosition, bool sustain)
{
    // Currently checks twice but why
    auto noteOnSampleLocation = getLocation(noteOnPosition);
    if (noteOnSampleLocation == -1) return;
    bufferMidiMessages.push_back(std::make_pair(noteOnMessage, noteOnSampleLocation));

    if (sustainToNextNote)
    {
        for (auto&& message : sustainedMidiMessages)
        {
            if (message.getNoteNumber() != noteOnMessage.getNoteNumber()) bufferMidiMessages.push_back(std::make_pair(message, noteOnSampleLocation));
        }
        sustainedMidiMessages.clear();
        sustainToNextNote = false;
    }

    if (sustain)
    {
        sustainedMidiMessages.push_back(noteOffMessage);
        sustainToNextNote = true;
    }
    else noteOffMessages.push_back(std::make_pair(noteOffMessage, noteOffPosition));
}

void MidiController::checkNoteOffMessages()
{
    auto copyOfMessages{ noteOffMessages };
    noteOffMessages.clear();
    for (auto&& message : copyOfMessages)
    {
        auto sampleLocation = getLocation(message.second);
        if (sampleLocation == -1) noteOffMessages.push_back(message);
        else bufferMidiMessages.push_back(std::make_pair(message.first, sampleLocation));
    }
}

int MidiController::getLocation(bars barPosition)
{
    // THIS NEEDS RETHINK - WHY ARE ALL YOUR SAMPLE LOCATIONS FLOATS?

    // fractional part is the location within a bar
    // whole part is the bar number

    auto sampleLocation = (barPosition * totalSampleLength) / totalNumberOfBars;

    if (sampleLocation >= sampleSpan.first && sampleLocation < sampleSpan.second)
    {
        return std::round(sampleLocation - sampleSpan.first);
    }
    if (sampleLocation >= sampleSpanOverspill.first && sampleLocation < sampleSpanOverspill.second)
    {
        return std::round(sampleLocation);
    }
    else return -1;
}
