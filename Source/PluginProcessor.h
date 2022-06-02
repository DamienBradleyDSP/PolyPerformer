/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Sequencer.h"

//==============================================================================
/**
*/
class PolyPerformerAudioProcessor  : public juce::AudioProcessor, public Button::Listener
{
public:
    //==============================================================================
    PolyPerformerAudioProcessor();
    ~PolyPerformerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void buttonClicked(juce::Button*) override;
    juce::String getPresetName();

private:

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    juce::ValueTree translatePolyManFile(juce::ValueTree,int moduleNumber);
    juce::ValueTree translatePolykolFile(juce::ValueTree, int moduleNumber);

    juce::UndoManager undoManager;
    juce::AudioProcessorValueTreeState parameters;

    Sequencer sequencer;
    juce::AudioPlayHead::CurrentPositionInfo currentpositionstruct;

    juce::ValueTree newPreset;
    std::array<juce::String, ProjectSettings::numberOfModules> moduleFileNames;

    int frameCounter = 0; // TESTING
    double srate;
    int buff;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolyPerformerAudioProcessor)
};
