/*
  ==============================================================================

    MidiController.cpp
    Created: 24 Oct 2021 4:19:29pm
    Author:  Damien

  ==============================================================================
*/

#include "MidiController.h"

MidiController::MidiController()
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
    reset = false;
}

void MidiController::calculateBufferSamples(juce::AudioPlayHead::CurrentPositionInfo& currentpositionstruct, bars totalNumOfBars)
{
    // THE SAMPLE COUNT SHOULD PROBABLY RESET OR BE CHECKED AT THE BAR LINE
    // 
    // Track the current bar using the current position struct.
    // When the bar ticks over we should be recalibrating our sample locations
    // 
    // We need to switch from a completely sample based engine here to a hybrid,
    // where It tracks bar locations and then map samples on to it
    // 
    // calculating sample ranges that 

    totalNumberOfBars = totalNumOfBars;
    double barsPerMinute = (double)currentpositionstruct.bpm / 4.0;
    oneBarSampleLength = ((4.0 * 60.0) / (double)currentpositionstruct.bpm) * sampleRate;
    totalSampleLength = (totalNumberOfBars / barsPerMinute) * 60.0 * sampleRate; //length in samples of the total number of bars spanned by the given rhythm modules

    if (reset) // User has pressed a note
    {
        sampleSpan.first = -1;
        sampleSpan.second = -1;
        sampleSpanOverspill.first = 0;
        sampleSpanOverspill.second = bufferLength - resetLocation;
        sampleOverspill = true;
        samplesFromRhythmStart = sampleSpanOverspill.second;
        reset = false;
        flushOldMessages();
    }
    else if ((samplesFromRhythmStart + (double)bufferLength) > totalSampleLength) // The loop is resetting during buffer
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

void MidiController::addMidiMessage(juce::MidiMessage& noteOnMessage, bars noteOnPosition, juce::MidiMessage& noteOffMessage, bars noteOffPosition, bool sustain)
{
    if (generateNewNotes() == false) return;

    // Currently checks twice but why
    auto noteOnSampleLocation = getLocation(noteOnPosition);
    if (noteOnSampleLocation == -1) return;

    modifyMessage(noteOnMessage, noteOnSampleLocation);
    modifyMessage(noteOffMessage, noteOnSampleLocation);

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

void MidiController::resetLoop(int bufferLocation)
{
    reset = true;
    resetLocation = bufferLocation;
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
        return std::round(bufferLength-sampleSpanOverspill.second+sampleLocation);
    }
    else return -1;
}

void MidiController::flushOldMessages()
{
    for(auto&& message : noteOffMessages) bufferMidiMessages.push_back(std::make_pair(message.first, 0));
    for(auto&& message : sustainedMidiMessages) bufferMidiMessages.push_back(std::make_pair(message, 0));

    noteOffMessages.clear();
    sustainedMidiMessages.clear();
}
