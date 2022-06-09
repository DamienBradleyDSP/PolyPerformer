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

    for (auto&& entry : midiNoteToSequencerMap) entry = nullptr;

    for (auto&& voice : midiVoices)
    {
        SequencerToMidiNoteMap.insert(std::make_pair(voice.get(), -1));
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

void SequencerModule::addMessage(juce::MidiMessage message)
{
    if (message.isNoteOn()) addNoteOn(message);
    else if (message.isNoteOff()) addNoteOff(message);
    else if (message.isSustainPedalOn() || message.isSustainPedalOff()) changeSustain(message);
}

void SequencerModule::replaceModuleState(std::unordered_map<juce::String, float>& moduleState)
{
    for (auto&& rhythm : rhythmModules) rhythm->replaceModuleState(moduleState);
}

void SequencerModule::addNoteOn(juce::MidiMessage message)
{
    auto midiNote = message.getNoteNumber();

    if (midiNoteToSequencerMap[message.getNoteNumber()] != nullptr) // if note already assigned to voice then retrigger
    {
        auto voice = midiNoteToSequencerMap[midiNote];
        voice->addNoteOn(message,sustainPedal);
        playingVoices.remove(voice); // use an iterator and erase!
        playingVoices.push_back(voice);

        midiNoteToSequencerMap[midiNote] = voice;
        SequencerToMidiNoteMap[voice] = midiNote;
    }
    else if (nonPlayingVoices.empty()) // if there are no unused voices - use a playing voice, oldest first
    {
        auto voice = playingVoices.front();
        voice->addNoteOn(message,sustainPedal);
        playingVoices.pop_front();
        playingVoices.push_back(voice);

        midiNoteToSequencerMap[midiNote] = voice;
        SequencerToMidiNoteMap[voice] = midiNote;
    }
    else // if there is an unused voice available
    {
        auto voice = nonPlayingVoices.front();
        voice->addNoteOn(message,sustainPedal);
        nonPlayingVoices.pop();
        playingVoices.push_back(voice);

        midiNoteToSequencerMap[midiNote] = voice;
        SequencerToMidiNoteMap[voice] = midiNote;
    }
}

void SequencerModule::addNoteOff(juce::MidiMessage message)
{

    if (midiNoteToSequencerMap[message.getNoteNumber()] == nullptr) return; // shouldnt be reached
    else
    {
        midiNoteToSequencerMap[message.getNoteNumber()]->addNoteOff(message);
    }
}

void SequencerModule::changeSustain(juce::MidiMessage message)
{
    sustainPedal = message.isSustainPedalOn();
    for (auto&& voice : midiVoices) voice->changeSustain(message);
}


