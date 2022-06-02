/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PolyPerformerAudioProcessorEditor::PolyPerformerAudioProcessorEditor (PolyPerformerAudioProcessor& p, AudioProcessorValueTreeState& parameters)
    : AudioProcessorEditor (&p), audioProcessor (p), gui(parameters,p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (515, 319);
    addAndMakeVisible(gui);

    loadSaveState = parameters.getRawParameterValue("loadSaveState");
}

PolyPerformerAudioProcessorEditor::~PolyPerformerAudioProcessorEditor()
{
}

//==============================================================================
void PolyPerformerAudioProcessorEditor::paint (juce::Graphics& g)
{
    if (loadSaveState->load())
    {
        loadSaveState->store(false); // hacky solution to ongoing APVTS problems
        gui.updateGui(audioProcessor.getPresetName());
    }
}

void PolyPerformerAudioProcessorEditor::resized()
{

    gui.setBounds(getLocalBounds());
}
