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

bool MidiVoice::isVoicePlaying()
{
    return isNotePlaying;
}

void MidiVoice::addNoteOn(juce::MidiMessage message, bool sustainPedal)
{
    isNoteDown = true;
    isSustainPedalDown = sustainPedal;
    releaseTriggered = false;
    turnVoiceOn(message);
}

void MidiVoice::addNoteOff(juce::MidiMessage message)
{
    isNoteDown = false;
    // if release already triggered, reset and return
    if (isSustainPedalDown) return;
    else triggerRelease();
}

void MidiVoice::changeSustain(juce::MidiMessage message)
{
    isSustainPedalDown = message.isSustainPedalOn();
    if (message.isSustainPedalOff() && !isNoteDown)
    {
        // trigger release
    }
}
void MidiVoice::triggerRelease()
{
    releaseTriggered = true;
    note.setTimeStamp(0);
    turnVoiceOff(note);
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

void MidiVoice::modifyMessage(juce::MidiMessage& message, int bufferLocation)
{
    message.setNoteNumber(note.getNoteNumber());
    message.setVelocity(message.getVelocity()*note.getVelocity());
}

bool MidiVoice::generateNewNotes()
{
    return isNotePlaying;
}

void MidiVoice::endOfBuffer()
{
    newNoteIncoming = false;
    // Check if release is at end, turn voice off for next buffer?
}