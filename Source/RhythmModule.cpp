/*
  ==============================================================================

    RhythmModule.cpp
    Created: 11 May 2022 2:49:42pm
    Author:  Damien

  ==============================================================================
*/

#include "RhythmModule.h"

RhythmModule::RhythmModule(juce::AudioProcessorValueTreeState& parameters, int rhythmNumber) :
    rhythmNumber(rhythmNumber)
{
    for (int beatNumber = 1; beatNumber <= ProjectSettings::maxNumberOfBeats; beatNumber++)
    {
        beats.push_back(Beat(parameters, rhythmNumber, beatNumber));
    }
}

RhythmModule::~RhythmModule()
{
}

void RhythmModule::generateMidi(std::list<MidiVoice*>& voices)
{
}

void RhythmModule::getNumberOfBars(bars& runningBarTotal)
{
}

bars RhythmModule::calculateBarSpan()
{
    return bars();
}
