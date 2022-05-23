/*
  ==============================================================================

    MidiVoice.h
    Created: 22 May 2022 4:57:09pm
    Author:  Damien

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "ProjectSettings.h"
#include "MidiController.h"

class MidiVoice
{
public:
    MidiVoice() = delete;
    MidiVoice(juce::AudioProcessorValueTreeState& parameters);
    ~MidiVoice();

    void initialise(double sampleRate, int bufferSize);

    // Midi Input Functions // Sequencer Module Interface
    bool midiInputMessage(MidiMessage message);

    // Midi Generation Functions // Sequencer Module Interface
    void prepareMidiControllers(juce::AudioPlayHead::CurrentPositionInfo& currentpositionstruct, bars totalNumberOfBars);
    void addMidiToBuffer(juce::MidiBuffer& buffer);

    // Midi Generation Functions // Beat Interface
    void addBeatMessage(juce::MidiMessage& noteOnMessage, bars noteOnPosition, juce::MidiMessage& noteOffMessage, bars noteOffPosition, bool sustain = false);

private:

    void addController();
    void removeController();

    double sampleRate;
    int bufferSize;

    // Voice Settings
    bool sustainedVoice = false;

    // Midi Controllers
    MidiController controller1;
    MidiController controller2;
    std::list<MidiController*> controllerList;

};