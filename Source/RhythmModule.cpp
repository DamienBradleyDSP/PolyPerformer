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
    moduleOnState.store(0);
}

RhythmModule::~RhythmModule()
{
}

void RhythmModule::generateMidi(std::list<MidiVoice*>& midiVoices)
{
    if (!moduleOnState.load()) return;

    auto beatNum = 1;
    for (auto&& beat : beats)
    {
        beat->setBarPositionLength((beatNum - 1) * numberOfBars.load() / numberOfBeats.load(), numberOfBars.load() / numberOfBeats.load());
        beat->applyMidiMessages(midiVoices, lastModuleBarEnding);

        if (beatNum >= ceil(selectedBeats.load())) break;
        beatNum++;
    }
}

void RhythmModule::getNumberOfBars(bars& runningBarTotal)
{
    // Adds the total number of bars that this module spans over to the total

    if (!moduleOnState.load()) return;
    lastModuleBarEnding = runningBarTotal;
    runningBarTotal += calculateBarSpan();
}

void RhythmModule::replaceModuleState(std::unordered_map<juce::String, float>& newState)
{
    for (auto&& beat : beats) beat->replaceModuleState(newState);

    moduleOnState.store(newState["moduleTurnedOn" + juce::String(rhythmNumber)]);
    numberOfBeats.store(newState["numberOfBeats" + juce::String(rhythmNumber)]);
    numberOfBars.store(newState["numberOfBars" + juce::String(rhythmNumber)]);
    selectedBeats.store(newState["selectionOfBeats" + juce::String(rhythmNumber)]);
}

bars RhythmModule::calculateBarSpan()
{

    bars barsPerBeat = numberOfBars.load() / numberOfBeats.load();
    bars selectedBarSpan = barsPerBeat * selectedBeats.load();

    return selectedBarSpan;
}


