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

    constexpr int midiChannel = 1;
    constexpr float midiVelocity= 1;
    constexpr int VoiceLimit = 16;
	constexpr int numberOfModules = 4;
	constexpr int midiNote = 72;
	constexpr int maxNumberOfRhythmModules = 32;
	constexpr int maxNumberOfBeats = 32;
	constexpr float numberOfSecondsBetweenRhythmChange = 2; // Time Linked random selection mode

	enum SequencerFileType
	{
		polykol = 0,
		polyman = 1, 
		midi = 2
	};
};
