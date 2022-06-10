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
    noteOn = juce::MidiMessage::noteOn(ProjectSettings::midiChannel, midiNote, (float)ProjectSettings::midiVelocity);
    noteOff = juce::MidiMessage::noteOff(ProjectSettings::midiChannel, midiNote);
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
    if (!onState.load()) return;

    auto noteNumber = midiNote + (midiOctave.load() * 12) + midiSemitone.load();
    noteOn.setNoteNumber(noteNumber);
    noteOff.setNoteNumber(noteNumber);

    noteOn.setVelocity(velocity.load());

    for(auto&& voice : midiVoices) voice->addMidiMessage(noteOn, lastModuleBarEnding + beatPosition, noteOff, lastModuleBarEnding + beatPosition + beatLength * noteLength.load(), sustain.load());
}

void Beat::replaceModuleState(std::unordered_map<juce::String, float>& newState)
{

    if (newState["fileType"] == ProjectSettings::SequencerFileType::polykol)
    {
        onState.store(newState["BeatOnOffR" + juce::String(rhythmNumber) + "B" + juce::String(beatNumber)]);
        velocity.store(newState["VelocityR" + juce::String(rhythmNumber) + "B" + juce::String(beatNumber)]);
        noteLength.store(newState["noteLengthR" + juce::String(rhythmNumber) + "B" + juce::String(beatNumber)]);
        //midiNote.store(newState["midiNoteNumber"]);
        midiSemitone.store(newState["SemitoneR" + juce::String(rhythmNumber) + "B" + juce::String(beatNumber)]);
        midiOctave.store(newState["OctaveR" + juce::String(rhythmNumber) + "B" + juce::String(beatNumber)]);
        sustain.store(newState["SustainR" + juce::String(rhythmNumber) + "B" + juce::String(beatNumber)]);
    }
    else if (newState["fileType"] == ProjectSettings::SequencerFileType::polyman)
    {
        onState.store(newState["beatOnOff" + juce::String(rhythmNumber) + "B" + juce::String(beatNumber)]);
        velocity.store(newState["velocityR" + juce::String(rhythmNumber) + "B" + juce::String(beatNumber)]);
        noteLength.store(0.999f);
        //midiNote.store(newState["midiNoteNumber"]);
        midiSemitone.store(0);
        midiOctave.store(0);
        sustain.store(1);
    }
    else jassertfalse;







    /*
    
    BARS TO REPEAT OVER!
    
    
    
    */

}
