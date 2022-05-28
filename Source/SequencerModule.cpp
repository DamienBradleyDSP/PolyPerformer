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
    for (int i = 0; i < ProjectSettings::VoiceLimit; i++) midiVoices.push_back(std::unique_ptr<MidiVoice>(new MidiVoice(parameters)));
    for (auto&& voice : midiVoices) nonPlayingVoices.push(voice.get());

    for (int i = 0; i < ProjectSettings::maxNumberOfRhythmModules; i++)
    {
        rhythmModules.push_back(std::unique_ptr<RhythmModule>(new RhythmModule(parameters,i)));
    }

    for (auto&& entry : midiNoteToSequencerMap)
    {
        entry = nullptr;
    }

}

SequencerModule::~SequencerModule()
{
}

void SequencerModule::initialise(double s, int b)
{
    for (auto&& voice : midiVoices) voice->initialise(s,b);
    sampleRate = s;
    bufferSize = b;
}

void SequencerModule::generateMidi(juce::MidiBuffer& buffer, juce::AudioPlayHead::CurrentPositionInfo& playhead)
{

    //!!!!!!!!!!!!!!!!
    bars totalNumberOfBars = barOffset; // replace with offset stat
    for (auto&& modu : rhythmModules) modu->getNumberOfBars(totalNumberOfBars);

    // calculate current sample range for buffer and get bar location

    for (auto&& voice : playingVoices) voice->calculateBufferSamples(playhead, totalNumberOfBars);
    for (auto&& rModule : rhythmModules) rModule->generateMidi(playingVoices);
    for (auto&& voice : playingVoices) voice->applyMidiMessages(buffer);
    for (auto&& voice : midiVoices) voice->endOfBuffer();

    auto copyOfMessages{ playingVoices };
    playingVoices.clear();
    for (auto&& message : copyOfMessages)
    {
        if (message->isVoicePlaying()) playingVoices.push_back(message);
        else nonPlayingVoices.push(message);
    }
}

void SequencerModule::addNoteOn(juce::MidiMessage message)
{
    if (midiNoteToSequencerMap[message.getNoteNumber()] != nullptr) // if note already assigned to voice then retrigger
    {
        auto voice = midiNoteToSequencerMap[message.getNoteNumber()];
        voice->turnVoiceOn(message);
        playingVoices.remove(voice); // use an iterator and erase!
        playingVoices.push_back(voice);
    }
    else if (nonPlayingVoices.empty()) // if there are no unused voices - use a playing voice, oldest first
    {
        auto voice = playingVoices.front();
        voice->turnVoiceOn(message);
        playingVoices.pop_front();
        playingVoices.push_back(voice);
        midiNoteToSequencerMap[message.getNoteNumber()] = voice;
    }
    else // if there is an unused voice available
    {
        auto voice = nonPlayingVoices.front();
        voice->turnVoiceOn(message);
        nonPlayingVoices.pop();
        playingVoices.push_back(voice);
        midiNoteToSequencerMap[message.getNoteNumber()] = voice;
    }
}

void SequencerModule::addNoteOff(juce::MidiMessage message)
{
    //if (midiNoteToSequencerMap[message.getNoteNumber()] == nullptr) jassertfalse; // shouldnt be reached
    if (midiNoteToSequencerMap[message.getNoteNumber()] == nullptr) return; // shouldnt be reached
    else
    {
        midiNoteToSequencerMap[message.getNoteNumber()]->turnVoiceOff(message);
    }
}

void SequencerModule::changeSustain(juce::MidiMessage message)
{
}
