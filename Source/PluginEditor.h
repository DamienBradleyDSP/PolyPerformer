/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "guiFiles/guiBounds.h"

//==============================================================================
/**
*/
class PolyPerformerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PolyPerformerAudioProcessorEditor (PolyPerformerAudioProcessor&, AudioProcessorValueTreeState& parameters);
    ~PolyPerformerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PolyPerformerAudioProcessor& audioProcessor;
    guiBounds gui;

    std::atomic<float>* loadSaveState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolyPerformerAudioProcessorEditor)
};
