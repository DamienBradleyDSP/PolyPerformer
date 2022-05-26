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
    onState = parameters.getRawParameterValue("BeatOnOffR" + juce::String(rhythmNumber) + "B" + juce::String(beatNumber));
    velocity = parameters.getRawParameterValue("VelocityR" + juce::String(rhythmNumber) + "B" + juce::String(beatNumber));
    noteLength = parameters.getRawParameterValue("noteLengthR" + juce::String(rhythmNumber) + "B" + juce::String(beatNumber));
    midiNote = parameters.getRawParameterValue("midiNoteNumber");
    midiSemitone = parameters.getRawParameterValue("SemitoneR" + juce::String(rhythmNumber) + "B" + juce::String(beatNumber));
    midiOctave = parameters.getRawParameterValue("OctaveR" + juce::String(rhythmNumber) + "B" + juce::String(beatNumber));
    sustain = parameters.getRawParameterValue("SustainR" + juce::String(rhythmNumber) + "B" + juce::String(beatNumber));

    noteOn = juce::MidiMessage::noteOn(ProjectSettings::midiChannel, midiNote->load(), (float)ProjectSettings::midiVelocity);
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

void Beat::applyMidiMessages(std::list<MidiVoice*>& midiVoices, bars lastModuleBarEnding)
{
    if (!onState->load()) return;

    auto noteNumber = midiNote->load() + (midiOctave->load() * 12) + midiSemitone->load();
    noteOn.setNoteNumber(noteNumber);
    noteOff.setNoteNumber(noteNumber);

    noteOn.setVelocity(velocity->load());

    for(auto&& voice : midiVoices) voice->addMidiMessage(noteOn, lastModuleBarEnding + beatPosition, noteOff, lastModuleBarEnding + beatPosition + beatLength * noteLength->load(), sustain->load());
}
