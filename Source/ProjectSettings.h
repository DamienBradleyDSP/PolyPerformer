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
    constexpr int maxNumberOfRhythmModules = 16;
    constexpr int maxNumberOfBeats = 16;
};
