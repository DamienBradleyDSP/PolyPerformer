/*
  ==============================================================================

    RhythmModule.cpp
    Created: 24 Oct 2021 4:19:47pm
    Author:  Damien

  ==============================================================================
*/

#include "RhythmModule.h"

RhythmModule::RhythmModule(juce::AudioProcessorValueTreeState& parameters, int rhythmNumber)
    : rhythmNumber(rhythmNumber)
{
    for (int beatNumber = 1; beatNumber <= ProjectSettings::maxNumberOfBeats; beatNumber++)
    {
        beats.push_back(std::unique_ptr<Beat>(new Beat(parameters, rhythmNumber, beatNumber)));
    }

    moduleOnState = parameters.getRawParameterValue("moduleTurnedOn" + juce::String(rhythmNumber));
    numberOfBeats = parameters.getRawParameterValue("numberOfBeats" + juce::String(rhythmNumber));
    numberOfBars = parameters.getRawParameterValue("numberOfBars" + juce::String(rhythmNumber));
    selectedBeats = parameters.getRawParameterValue("selectionOfBeats" + juce::String(rhythmNumber));
}

RhythmModule::~RhythmModule()
{
}

void RhythmModule::generateMidi(std::list<MidiVoice*>& midiVoices)
{
    if (!moduleOnState->load()) return;

    auto beatNum = 1;
    for (auto&& beat : beats)
    {
        beat->setBarPositionLength((beatNum - 1) * numberOfBars->load() / numberOfBeats->load(), numberOfBars->load() / numberOfBeats->load());
        beat->applyMidiMessages(midiVoices, lastModuleBarEnding);

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


