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

    bars totalNumberOfBars = barOffset; // replace with offset stat
    for (auto&& modu : rhythmModules) modu.getNumberOfBars(totalNumberOfBars);

    // calculate current sample range for buffer and get bar location

    for (auto voice : playingVoices) voice->exposeMidiController().calculateBufferSamples(playhead, totalNumberOfBars);
    for (auto&& rModule : rhythmModules) rModule.generateMidi(playingVoices);
    for (auto voice : playingVoices) voice->exposeMidiController().applyMidiMessages(buffer);
}

void SequencerModule::addNoteOn(juce::MidiMessage message, int sampleLocation)
{
    for (auto&& voice : playingVoices)
    {
        if (message.getNoteNumber() == voice->getNoteNumber())
        {
            voice->addNoteOn(message, sampleLocation);
            playingVoices.remove(voice);
            playingVoices.push_back(voice);
            return;
        }
    }

    if (playingVoices.size() != ProjectSettings::VoiceLimit)
    {
        // register note on with non playing voice, remove from non playing voice and push on to playing voice at back
        auto newVoice = nonPlayingVoices.front();
        nonPlayingVoices.pop();
        newVoice->addNoteOn(message, sampleLocation);
        playingVoices.push_back(newVoice);
    }
    else
    {
        // register note on with first playing voice, remove and push to back
        auto oldVoice = playingVoices.front();
        oldVoice->addNoteOn(message, sampleLocation);
        playingVoices.push_back(oldVoice);
        playingVoices.pop_front();
    }
}

void SequencerModule::addNoteOff(juce::MidiMessage message, int sampleLocation)
{
    for (auto&& voice : playingVoices)
    {
        // check if note off matches
        // if it does, register note off, remove from list and add to non playing voices
        if (voice->getNoteNumber() != message.getNoteNumber()) continue;

        if(!voice->addNoteOff(sampleLocation)) return;
        nonPlayingVoices.push(voice);
        playingVoices.remove(voice);
        return;
    }
}

void SequencerModule::changeSustain(bool sustain, int sampleLocation)
{
    for (auto&& voice : playingVoices) voice->changeSustain(sustain, sampleLocation);
}

void SequencerModule::removeSustainedNote(int noteNumber, int sampleLocation)
{
    for (auto&& voice : playingVoices)
    {
        // check if note off matches
        // if it does, register a specific sustained note off, remove from list and add to non playing voices
        if (voice->getNoteNumber() != noteNumber) continue;
        
        voice->removeSustainedNote(sampleLocation);
        nonPlayingVoices.push(voice);
        playingVoices.remove(voice);
        return;
    }
}
