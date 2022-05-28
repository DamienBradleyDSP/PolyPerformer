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
    bool isVoicePlaying();

    void addNoteOn(juce::MidiMessage message);
    void addNoteOff(juce::MidiMessage message);
    void changeSustain(juce::MidiMessage message);
    // HANDLE SUSTAIN OUTSIDE THIS CLASS!
    // CHANGE TO JUST "TURN ON" "TURN OFF" AND FEED IN A TRIGGER TO A VELOCITY DROP TO MIMIC SUSTAIN
private:
    void turnVoiceOn(juce::MidiMessage message);
    void turnVoiceOff(juce::MidiMessage message);
    void triggerRelease();
    void modifyMessage(juce::MidiMessage& message, int bufferLocation) override;
    bool generateNewNotes() override;

    juce::MidiMessage note;
    bool newNoteIncoming = false;
    int newNoteBufferLocation=0;

    bool isNotePlaying = false;
    bool isNoteDown = false;
    bool isSustainPedalDown = false;

};