/*
  ==============================================================================

    MidiVoice.cpp
    Created: 22 May 2022 4:57:10pm
    Author:  Damien

  ==============================================================================
*/

#include "MidiVoice.h"

MidiVoice::MidiVoice(juce::AudioProcessorValueTreeState& parameters) :
    midiController(parameters)
{
}

MidiVoice::~MidiVoice()
{
}

void MidiVoice::initialise(double sampleRate, int bufferSize)
{
    midiController.initialise(sampleRate,bufferSize);
}

int MidiVoice::getNoteNumber()
{
    return midiNoteNumber;
}

void MidiVoice::addNoteOn(MidiMessage message, int sampleLocation)
{
    // EDGE CASE - WHAT HAPPENS WHEN A USER PRESSES A NOTE, THE NOTE WILL CHANGE EARLY

    midiNoteNumber = message.getNoteNumber();
    midiController.resetRhythmTrack(sampleLocation);
}

bool MidiVoice::addNoteOff(int sampleLocation)
{
    if (sustain) return false;
    midiController.resetRhythmTrack(sampleLocation);
    midiNoteNumber = -1;

    return true;
}

void MidiVoice::changeSustain(bool flag, int sampleLocation)
{
    sustain = flag;
}

void MidiVoice::removeSustainedNote(int sampleLocation)
{
    sustain = false;
    addNoteOff(sampleLocation);
}

MidiController& MidiVoice::exposeMidiController()
{
    return midiController;
}

void MidiVoice::addMidiMessage(juce::MidiMessage const& noteOnMessage, bars noteOnPosition, juce::MidiMessage const& noteOffMessage, bars noteOffPosition, bool sustain)
{
}
