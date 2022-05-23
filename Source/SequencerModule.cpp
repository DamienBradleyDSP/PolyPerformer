/*
  ==============================================================================

    SequencerModule.cpp
    Created: 11 May 2022 2:49:33pm
    Author:  Damien

  ==============================================================================
*/

#include "SequencerModule.h"

SequencerModule::SequencerModule(juce::AudioProcessorValueTreeState& parameters) :
    midiVoices(ProjectSettings::VoiceLimit,MidiVoice(parameters))
{
    for (auto&& voice : midiVoices) nonPlayingVoices.push(&voice);
    for (auto&& voice : midiVoices) mapVoiceToNote.insert(std::make_pair(&voice,-1));

    for (int i = 0; i < ProjectSettings::maxNumberOfRhythmModules; i++)
    {
        rhythmModules.push_back(RhythmModule(parameters, i));
    }

}

SequencerModule::~SequencerModule()
{
}

void SequencerModule::initialise(double s, int b)
{
    for (auto&& voice : midiVoices) voice.initialise(s,b);
}

void SequencerModule::generateMidi(juce::MidiBuffer& buffer, juce::AudioPlayHead::CurrentPositionInfo& playhead)
{
    // For module, if its turned on, add the bars to the total number of bars - ORDER SENSITIVE

    //!!!!!!!!!!!!!!!!
    bars totalNumberOfBars = barOffset; // replace with offset stat
    for (auto&& modu : rhythmModules) modu.getNumberOfBars(totalNumberOfBars);

    // calculate current sample range for buffer and get bar location

    for (auto voice : playingVoices) voice->prepareMidiControllers(playhead, totalNumberOfBars);
    for (auto&& rModule : rhythmModules) rModule.generateMidi(playingVoices);
    for (auto voice : playingVoices) voice->addMidiToBuffer(buffer);

    for (auto&& voice : voicesStoppingAtBufferEnd)
    {
        nonPlayingVoices.push(*voice);
        playingVoices.erase(voice);
    }
}

void SequencerModule::addNoteOn(juce::MidiMessage message)
{
    for (auto&& voice : playingVoices)
    {
        if (message.getNoteNumber() == mapVoiceToNote[voice])
        {
            mapVoiceToNote[voice] = message.getNoteNumber();
            voice->midiInputMessage(message);
            playingVoices.remove(voice);
            playingVoices.push_back(voice);
            return;
        }
    }
    if (playingVoices.size() != ProjectSettings::VoiceLimit)
    {
        // register note on with non playing voice, remove from non playing voice and push on to playing voice at back
        auto newVoice = nonPlayingVoices.front();
        mapVoiceToNote[newVoice] = message.getNoteNumber();
        nonPlayingVoices.pop();
        newVoice->midiInputMessage(message);
        playingVoices.push_back(newVoice);
    }
    else
    {
        // register note on with first playing voice, remove and push to back
        auto oldVoice = playingVoices.front();
        mapVoiceToNote[oldVoice] = message.getNoteNumber();
        oldVoice->midiInputMessage(message);
        playingVoices.push_back(oldVoice);
        playingVoices.pop_front();
    }
}

void SequencerModule::addNoteOff(juce::MidiMessage message)
{
    for (auto voiceIterator = playingVoices.begin(); voiceIterator!=playingVoices.end(); voiceIterator++)
    {
        if (mapVoiceToNote[*voiceIterator] != message.getNoteNumber()) continue;

        if(!(*voiceIterator)->midiInputMessage(message)) return;

        mapVoiceToNote[*voiceIterator] = -1;
        voicesStoppingAtBufferEnd.push_back(voiceIterator);
        return;
    }
}

void SequencerModule::changeSustain(juce::MidiMessage message)
{
    for (auto&& voice : playingVoices) voice->midiInputMessage(message);
}
