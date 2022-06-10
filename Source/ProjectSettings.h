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
    constexpr int VoiceLimit = 16;
	constexpr int numberOfModules = 4;
	constexpr int midiNote = 72;

	enum SequencerFileType
	{
		polykol = 0,
		polyman = 1, 
		midi = 2
	};


	// POLYKOL PARAM ANALYSIS DEFAULTS
	constexpr int polykolMaximumRhythmModules = 32;

	//POLYKOL IMPORTED SETTINGS
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
	//constexpr int midiChannel = 1;
	//constexpr int midiNote = 36;
	constexpr float midiVelocity = 0.5;

	// POLYMAN ADDITIONAL

	constexpr int maxNumberPolymanRhythms = 5;
	constexpr int minNumberOfBarsToRepeatOver = 1;
	constexpr int maxNumberOfBarsToRepeatOver = 32;
};
