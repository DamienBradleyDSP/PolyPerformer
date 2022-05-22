/*
  ==============================================================================

    MidiVoice.h
    Created: 22 May 2022 4:57:09pm
    Author:  Damien

  ==============================================================================
*/

#pragma once
#include "MidiController.h"
#include "ProjectSettings.h"

class MidiVoice
{
public:
    MidiVoice() = delete;
    MidiVoice(juce::AudioProcessorValueTreeState& parameters);
    ~MidiVoice();

    void initialise(double sampleRate, int bufferSize);

    // Midi Input Functions // Sequencer Module Interface
    int getNoteNumber();
    void addNoteOn(MidiMessage message, int sampleLocation);
    bool addNoteOff(int sampleLocation);
    void changeSustain(bool sustain, int sampleLocation);
    void removeSustainedNote(int sampleLocation);

    // Exposing MidiController to Sequencer Module // Sequencer Module Interface
    MidiController& exposeMidiController();

    // Midi Generation Functions // Beat interface
    void addMidiMessage(juce::MidiMessage const& noteOnMessage, bars noteOnPosition, juce::MidiMessage const& noteOffMessage, bars noteOffPosition, bool sustain = false);

private:

    MidiController midiController;

    int midiNoteNumber = -1;
    bool sustain = false;


    // add sustains and velocity stuff here
};