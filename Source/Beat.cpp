/*
  ==============================================================================

    Beat.cpp
    Created: 25 Oct 2021 3:55:25pm
    Author:  Damien

  ==============================================================================
*/

#include "Beat.h"

Beat::Beat(juce::AudioProcessorValueTreeState& parameters, int rnum, int bnum)
    : rhythmNumber(rnum), beatNumber(bnum)
{
    onState = new std::atomic<float>(1);
    velocity = new std::atomic<float>(1);
    noteLength = new std::atomic<float>(1);
    midiNote = new std::atomic<float>(72);
    midiSemitone = new std::atomic<float>(0);
    midiOctave = new std::atomic<float>(1);
    sustain = new std::atomic<float>(0);

    noteOn = juce::MidiMessage::noteOn(ProjectSettings::midiChannel, midiNote->load(), 1.0f);
    noteOff = juce::MidiMessage::noteOff(ProjectSettings::midiChannel, midiNote->load());
    allNotesOff = juce::MidiMessage::allNotesOff(ProjectSettings::midiChannel);
}

Beat::~Beat()
{
}

void Beat::setBarPositionLength(bars barPosition, bars length)
{
    beatPosition = barPosition;
    beatLength = length;
}

void Beat::applyMidiMessages(std::unique_ptr<MidiController>& midiController, bars lastModuleBarEnding)
{
    if (!onState->load()) return;

    auto noteNumber = midiNote->load() + (midiOctave->load() * 12) + midiSemitone->load();
    noteOn.setNoteNumber(noteNumber);
    noteOff.setNoteNumber(noteNumber);

    noteOn.setVelocity(velocity->load());

    midiController->addMidiMessage(noteOn, lastModuleBarEnding + beatPosition,noteOff, lastModuleBarEnding + beatPosition + beatLength * noteLength->load(),sustain->load());
}
