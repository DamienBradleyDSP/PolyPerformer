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

void MidiVoice::endOfBuffer()
{
    newNoteIncoming = false;
    //currentNote = newNote;
}

bool MidiVoice::modifyMessage(juce::MidiMessage& message, int bufferLocation)
{
    message.setNoteNumber(currentNote.getNoteNumber());
    if (newNoteIncoming && bufferLocation < newNoteBufferLocation) return false;
    else if (!notePlaying) return false;
    else return true;
}

void MidiVoice::noteOn(juce::MidiMessage message)
{
    currentNote = message;
    newNoteBufferLocation = message.getTimeStamp();
    newNoteIncoming = true;
    resetLoop(message.getTimeStamp());
    notePlaying = true;
}

void MidiVoice::noteOff(juce::MidiMessage message)
{
    resetLoop(message.getTimeStamp());
    notePlaying = false;
}

bool MidiVoice::isVoicePlaying()
{
    return notePlaying;
}
