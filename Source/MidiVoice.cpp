/*
  ==============================================================================

    MidiVoice.cpp
    Created: 26 May 2022 4:58:50pm
    Author:  Damien

  ==============================================================================
*/

#include "MidiVoice.h"

MidiVoice::MidiVoice(AudioProcessorValueTreeState& parameters, int m)
    : moduleNumber(m)
{
    note = juce::MidiMessage::noteOn(ProjectSettings::midiChannel, ProjectSettings::midiNote, (float)ProjectSettings::midiVelocity);

    releaseTime = parameters.getRawParameterValue("moduleRelease" + juce::String(moduleNumber));
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
    releaseVelocity = 0.0f;
    releaseBufferIncrement = 0.0f;
    turnVoiceOn(message);
}

void MidiVoice::addNoteOff(juce::MidiMessage message)
{
    isNoteDown = false;
    // if release already triggered, reset and return
    if (isSustainPedalDown) return;
    else triggerRelease(message);
}

void MidiVoice::changeSustain(juce::MidiMessage message)
{
    isSustainPedalDown = message.isSustainPedalOn();
    if (message.isSustainPedalOff() && !isNoteDown)
    {
        triggerRelease(message);
    }
}
void MidiVoice::forceVoiceOff(juce::MidiMessage message)
{
    turnVoiceOff(message);
}
void MidiVoice::triggerRelease(juce::MidiMessage message)
{
    
    auto numberOfBuffersToNoteEnd = (releaseTime->load()*sampleRate)/bufferLength; // 1/(releaseInSeconds*sampleRate/bufferLength) = numberOfbuffers increments needed to get to 0
    
    if (numberOfBuffersToNoteEnd == 0.0f) turnVoiceOff(message);
    else
    {
        releaseTriggered = true;
        releaseVelocity = 0.0f;
        releaseBufferIncrement = 1 / numberOfBuffersToNoteEnd;
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

void MidiVoice::modifyMessage(juce::MidiMessage& message, int bufferLocation)
{
    message.setNoteNumber(note.getNoteNumber());
    message.setVelocity(message.getFloatVelocity()*note.getFloatVelocity() - releaseVelocity);
}

bool MidiVoice::generateNewNotes()
{
    return isNotePlaying;
}

void MidiVoice::startOfBuffer()
{
    newNoteIncoming = false;
    if (releaseTriggered) releaseVelocity += releaseBufferIncrement;
    if (releaseVelocity >= 1.0f)
    {
        releaseTriggered = false;
        turnVoiceOff(note);
    }
    // Check if release is at end, turn voice off for next buffer?
}