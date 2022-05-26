/*
  ==============================================================================

    ProjectSettings.h
    Created: 11 May 2022 3:53:55pm
    Author:  Damien

  ==============================================================================
*/

#pragma once

// Some typedefs to aid understanding of engine maths
typedef float samples; // units of samples
typedef float bars;

namespace ProjectSettings
{
    //Functional Settings 

    //constexpr int midiChannel = 1;
    constexpr int VoiceLimit = 16;







	constexpr int startingNumberOfBeats = 4;
	constexpr int startingNumberOfBars = 1;
	constexpr int startingSemitone = 0;
	constexpr int startingOctave = 0;
	constexpr int startingNumberOfRhythmModules = 1;
	constexpr int minNumberOfRhythmModules = 1;
	constexpr int maxNumberOfRhythmModules = 32;
	constexpr int minNumberOfBeats = 1;
	constexpr int maxNumberOfBeats = 32;
	constexpr int minNumberOfBars = 1;
	constexpr int maxNumberOfBars = 8;


	constexpr int midiChannel = 1;
	constexpr int midiNote = 36;
	constexpr float midiVelocity = 0.5;
};
