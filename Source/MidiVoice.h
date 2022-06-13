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
    MidiVoice(AudioProcessorValueTreeState& parameters, int moduleNumber);
    ~MidiVoice();

    void startOfBuffer();

    bool isVoicePlaying();
    void addNoteOn(juce::MidiMessage message, bool sustainPedal);
    void addNoteOff(juce::MidiMessage message);
    void changeSustain(juce::MidiMessage message);
    // HANDLE SUSTAIN OUTSIDE THIS CLASS!
    // CHANGE TO JUST "TURN ON" "TURN OFF" AND FEED IN A TRIGGER TO A VELOCITY DROP TO MIMIC SUSTAIN
private:
    void triggerRelease(juce::MidiMessage message);
    void turnVoiceOn(juce::MidiMessage message);
    void turnVoiceOff(juce::MidiMessage message);
    

    void modifyMessage(juce::MidiMessage& message, int bufferLocation) override;
    bool generateNewNotes() override;
    
    const int moduleNumber;

    // Internal Note Logic
    juce::MidiMessage note;
    bool newNoteIncoming = false;
    int newNoteBufferLocation=0;
    bool isNotePlaying = false;

    // Midi Input Logic
    bool isNoteDown = false;
    bool isSustainPedalDown = false;
    bool releaseTriggered = false;

    std::atomic<float>* releaseTime; // user set release time
    float releaseVelocity = 0.0f;
    float releaseBufferIncrement = 0.0f;

};