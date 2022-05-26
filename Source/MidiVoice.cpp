/*
  ==============================================================================

    MidiVoice.cpp
    Created: 26 May 2022 4:58:50pm
    Author:  Damien

  ==============================================================================
*/

#include "MidiVoice.h"

MidiVoice::MidiVoice(AudioProcessorValueTreeState& parameters)
{
    currentNote = juce::MidiMessage::noteOn(ProjectSettings::midiChannel, ProjectSettings::midiNote, (float)ProjectSettings::midiVelocity);
    newNote = juce::MidiMessage::noteOn(ProjectSettings::midiChannel, ProjectSettings::midiNote, (float)ProjectSettings::midiVelocity);
}

MidiVoice::~MidiVoice()
{
}

void MidiVoice::startOfNewBuffer()
{
    newNoteIncoming = false;
    currentNote = newNote;
}

void MidiVoice::modifyMessage(juce::MidiMessage& message, int bufferLocation)
{
    if (newNoteIncoming && bufferLocation >= newNoteBufferLocation) message.setNoteNumber(newNote.getNoteNumber());
    else message.setNoteNumber(currentNote.getNoteNumber());
}

void MidiVoice::noteOn(juce::MidiMessage message)
{
    newNote = message;
    newNoteBufferLocation = message.getTimeStamp();
    newNoteIncoming = true;
    startLoop(message.getTimeStamp());
}

void MidiVoice::noteOff(juce::MidiMessage message)
{
    stopLoop(message.getTimeStamp());
}
