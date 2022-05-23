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
    noteOn = juce::MidiMessage::noteOn(ProjectSettings::midiChannel, midiNote->load(), 1.0f);
    noteOff = juce::MidiMessage::noteOff(ProjectSettings::midiChannel, midiNote->load());
    allNotesOff = juce::MidiMessage::allNotesOff(ProjectSettings::midiChannel);
}

Beat::~Beat()
{
}

void Beat::setBarPositionLength(bars barPosition, bars length)
{
    beatPosition = barPosition;
    beatLength = length;
}

void Beat::applyMidiMessages(std::list<MidiVoice*>& voices, bars lastModuleBarEnding)
{
    if (!onState->load()) return;

    auto noteNumber = midiNote->load() + (midiOctave->load() * 12) + midiSemitone->load();
    noteOn.setNoteNumber(noteNumber);
    noteOff.setNoteNumber(noteNumber);

    noteOn.setVelocity(velocity->load());

    for(auto&& voice : voices) voice->addBeatMessage(noteOn, lastModuleBarEnding + beatPosition, noteOff, lastModuleBarEnding + beatPosition + beatLength * noteLength->load(), sustain->load());
}
