/*
  ==============================================================================

    Beat.cpp
    Created: 11 May 2022 2:50:05pm
    Author:  Damien

  ==============================================================================
*/

#include "Beat.h"

Beat::Beat(juce::AudioProcessorValueTreeState& parameters, int rhythmNumber, int beatNumber) :
    rhythmNumber(rhythmNumber),
    beatNumber(beatNumber)
{
}

Beat::~Beat()
{
}

void Beat::setBarPositionLength(bars barPosition, bars length)
{
}

void Beat::applyMidiMessages(std::list<MidiVoice*>& voices, bars lastModuleBarEnding)
{
}
