/*
  ==============================================================================

    SequencerModule.cpp
    Created: 11 May 2022 2:49:33pm
    Author:  Damien

  ==============================================================================
*/

#include "SequencerModule.h"

SequencerModule::SequencerModule(juce::AudioProcessorValueTreeState& parameters)
{
    for (int i = 0; i < ProjectSettings::VoiceLimit; i++) midiVoices.push_back(std::unique_ptr<MidiController>(new MidiController));
    for (auto&& voice : midiVoices) nonPlayingVoices.push(voice.get());
    for (auto&& voice : midiVoices) mapVoiceToNote.insert(std::make_pair(voice.get(),-1));

    for (int i = 0; i < ProjectSettings::maxNumberOfRhythmModules; i++)
    {
        rhythmModules.push_back(std::unique_ptr<RhythmModule>(new RhythmModule(parameters,i)));
    }

}

SequencerModule::~SequencerModule()
{
}

void SequencerModule::initialise(double s, int b)
{
    for (auto&& voice : midiVoices) voice->initialise(s,b);
}

void SequencerModule::generateMidi(juce::MidiBuffer& buffer, juce::AudioPlayHead::CurrentPositionInfo& playhead)
{
    // For module, if its turned on, add the bars to the total number of bars - ORDER SENSITIVE
    if (!noteOn) return;

    //!!!!!!!!!!!!!!!!
    bars totalNumberOfBars = barOffset; // replace with offset stat
    for (auto&& modu : rhythmModules) modu->getNumberOfBars(totalNumberOfBars);

    // calculate current sample range for buffer and get bar location

    midiVoices[0]->calculateBufferSamples(playhead, totalNumberOfBars);
    for (auto&& rModule : rhythmModules) rModule->generateMidi(midiVoices[0]);
    midiVoices[0]->applyMidiMessages(buffer);
}

void SequencerModule::addNoteOn(juce::MidiMessage message)
{
    midiVoices[0]->resetLoop(message.getTimeStamp());
    noteOn = true;
}

void SequencerModule::addNoteOff(juce::MidiMessage message)
{
    noteOn = false;
}

void SequencerModule::changeSustain(juce::MidiMessage message)
{
}
