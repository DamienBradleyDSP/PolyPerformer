/*
  ==============================================================================

    MidiVoice.cpp
    Created: 22 May 2022 4:57:10pm
    Author:  Damien

  ==============================================================================
*/

#include "MidiVoice.h"

MidiVoice::MidiVoice(juce::AudioProcessorValueTreeState& parameters) :
    controller1(parameters),
    controller2(parameters)
{
}

MidiVoice::~MidiVoice()
{
}

void MidiVoice::initialise(double s, int b)
{
    sampleRate = s;
    bufferSize = b;
    controller1.initialise(s, b);
    controller2.initialise(s, b);
    controllerList.clear();
    controllerList.push_back(&controller1);
}

// MIDI VOICE

bool MidiVoice::midiInputMessage(MidiMessage message)
{
    if (sustainedVoice && message.isNoteOff() && !message.isSustainPedalOff()) return false;
    if (message.isSustainPedalOn()) sustainedVoice = true;
    if (message.isSustainPedalOff()) sustainedVoice = false;
    addController();
    controllerList.front()->controllerTurningOff(message);
    controllerList.back()->controllerTurningOn(message);
    return true;
}

void MidiVoice::prepareMidiControllers(juce::AudioPlayHead::CurrentPositionInfo& currentpositionstruct, bars totalNumberOfBars)
{
    for (auto&& controller : controllerList) controller->calculateBufferSamples(currentpositionstruct, totalNumberOfBars);
}

void MidiVoice::addMidiToBuffer(juce::MidiBuffer& buffer)
{
    for (auto&& controller : controllerList) controller->applyMidiMessages(buffer);
    removeController();
}

void MidiVoice::addBeatMessage(juce::MidiMessage& noteOnMessage, bars noteOnPosition, juce::MidiMessage& noteOffMessage, bars noteOffPosition, bool sustain)
{
    for (auto&& controller : controllerList) controller->addMidiMessage(noteOnMessage,noteOnPosition,noteOffMessage,noteOffPosition,sustain);
}

void MidiVoice::addController()
{
    if (controllerList.size() == 1)
    {
        if (&controller1 == controllerList.front()) controllerList.push_back(&controller2);
        else controllerList.push_back(&controller1);
    }
    else return;
}

void MidiVoice::removeController()
{
    if (controllerList.size() > 1)
    {
        controllerList.back()->copyMidiList(controllerList.front());
        controllerList.front()->initialise(sampleRate, bufferSize);
        controllerList.pop_front();
    }
    else return;
}



