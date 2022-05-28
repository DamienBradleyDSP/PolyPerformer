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
    void turnVoiceOn(juce::MidiMessage message);
    void turnVoiceOff(juce::MidiMessage message);
    void triggerReleaseGraph(float timeInSamples);
    bool isVoicePlaying();
    // HANDLE SUSTAIN OUTSIDE THIS CLASS!
    // CHANGE TO JUST "TURN ON" "TURN OFF" AND FEED IN A TRIGGER TO A VELOCITY DROP TO MIMIC SUSTAIN
private:
    void modifyMessage(juce::MidiMessage& message, int bufferLocation) override;
    bool generateNewNotes() override;

    juce::MidiMessage currentNote;

    bool newNoteIncoming = false;
    int newNoteBufferLocation=0;
    juce::MidiMessage newNote;

    bool notePlaying = true;
};