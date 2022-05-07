/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PolyPerformerAudioProcessorEditor::PolyPerformerAudioProcessorEditor (PolyPerformerAudioProcessor& p, AudioProcessorValueTreeState& parameters)
    : AudioProcessorEditor (&p), audioProcessor (p), gui(parameters)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (515, 319);
    addAndMakeVisible(gui);
}

PolyPerformerAudioProcessorEditor::~PolyPerformerAudioProcessorEditor()
{
}

//==============================================================================
void PolyPerformerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
}

void PolyPerformerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    gui.setBounds(getLocalBounds());
}
