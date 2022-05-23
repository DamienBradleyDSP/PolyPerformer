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
    if (!moduleOnState->load()) return;

    auto beatNum = 1;
    for (auto&& beat : beats)
    {
        beat.setBarPositionLength((beatNum - 1) * numberOfBars->load() / numberOfBeats->load(), numberOfBars->load() / numberOfBeats->load());
        beat.applyMidiMessages(voices, lastModuleBarEnding);

        if (beatNum >= ceil(selectedBeats->load())) break;
        beatNum++;
    }
}

void RhythmModule::getNumberOfBars(bars& runningBarTotal)
{
    // Adds the total number of bars that this module spans over to the total

    if (!moduleOnState->load()) return;
    lastModuleBarEnding = runningBarTotal;
    runningBarTotal += calculateBarSpan();
}

bars RhythmModule::calculateBarSpan()
{
    bars barsPerBeat = numberOfBars->load() / numberOfBeats->load();
    bars selectedBarSpan = barsPerBeat * selectedBeats->load();

    return selectedBarSpan;
}
