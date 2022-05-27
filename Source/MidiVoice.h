/*
  ==============================================================================

    MidiVoice.h
    Created: 26 May 2022 4:58:50pm
    Author:  Damien

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "MidiController.h"

class MidiVoice : public MidiController
{
public:
    MidiVoice()=delete;
    MidiVoice(AudioProcessorValueTreeState& parameters);
    ~MidiVoice();

    void endOfBuffer();
    void modifyMessage(juce::MidiMessage& message, int bufferLocation) override;

    void noteOn(juce::MidiMessage message);
    void noteOff(juce::MidiMessage message);
    bool isVoicePlaying();
    // HANDLE SUSTAIN OUTSIDE THIS CLASS!
    // CHANGE TO JUST "TURN ON" "TURN OFF" AND FEED IN A TRIGGER TO A VELOCITY DROP TO MIMIC SUSTAIN
protected:
    bool generateNotes();
private:
    juce::MidiMessage currentNote;

    bool newNoteIncoming = false;
    int newNoteBufferLocation=0;
    juce::MidiMessage newNote;

    bool notePlaying = true;
};