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
    note = juce::MidiMessage::noteOn(ProjectSettings::midiChannel, ProjectSettings::midiNote, (float)ProjectSettings::midiVelocity);
}

MidiVoice::~MidiVoice()
{
}

void MidiVoice::endOfBuffer()
{
    newNoteIncoming = false;
    //currentNote = newNote;
}

bool MidiVoice::isVoicePlaying()
{
    return isNotePlaying;
}

void MidiVoice::addNoteOn(juce::MidiMessage message)
{
    isNoteDown = true;
    turnVoiceOn(message);
}

void MidiVoice::addNoteOff(juce::MidiMessage message)
{
    isNoteDown = false;
    // if release already triggered, reset and return
    if (isSustainPedalDown) return;
    else
    {
        // trigger release
    }
}

void MidiVoice::changeSustain(juce::MidiMessage message)
{
    // if release triggered, return
    isSustainPedalDown = message.isSustainPedalOn();
    if (message.isSustainPedalOff() && !isNoteDown)
    {
        // trigger release
    }
}

void MidiVoice::turnVoiceOn(juce::MidiMessage message)
{
    note = message;
    newNoteBufferLocation = message.getTimeStamp();
    newNoteIncoming = true;
    resetLoop(message.getTimeStamp());
    isNotePlaying = true;
}

void MidiVoice::turnVoiceOff(juce::MidiMessage message)
{
    resetLoop(message.getTimeStamp());
    isNotePlaying = false;
}

void MidiVoice::triggerRelease()
{
}

void MidiVoice::modifyMessage(juce::MidiMessage& message, int bufferLocation)
{
    message.setNoteNumber(note.getNoteNumber());
    message.setVelocity(message.getVelocity()*note.getVelocity());
}

bool MidiVoice::generateNewNotes()
{
    return isNotePlaying;
}