/*
  ==============================================================================

	THIS CODE WAS AUTOMATICALLY GENERATED

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "polyModule.h"

//==============================================================================
polyModule::polyModule(AudioProcessorValueTreeState& parameters)
	: unusedmember(0)
// >>>>INITIALISATION>>>> (auto-generated)//
, noteSelector1(parameters)
, OnOffButton1(parameters)
, rhythmLoader1(parameters)
// <<<<INITIALISATION<<<< (will be overwritten!!)   
{
	// >>>>CONSTRUCTOR>>>> (auto-generated)//
	addAndMakeVisible(sustainSliderSlider1);
	auto sliderLookFeel = new sustainSlider();
	sustainSliderSlider1.setLookAndFeel(sliderLookFeel);
	sustainSliderSlider1.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	sustainSliderSlider1.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	addAndMakeVisible(noteSelector1);
	addAndMakeVisible(OnOffButton1);
	addAndMakeVisible(rhythmLoader1);
	// <<<<CONSTRUCTOR<<<< (will be overwritten!!)   
}

polyModule::~polyModule()
{
}

void polyModule::paint (Graphics& g)
{
	// >>>>PAINT>>>> (auto-generated)//
	// <<<<PAINT<<<< (will be overwritten!!)
}

void polyModule::resized()
{
	// >>>>RESIZED>>>> (auto-generated)//
	sustainSliderSlider1.setBounds(322,8,27,32);
	noteSelector1.setBounds(49,3,42,42);
	OnOffButton1.setBounds(0,0,48,48);
	rhythmLoader1.setBounds(109,4,201,40);
	// <<<<RESIZED<<<< (will be overwritten!!)
}

// >>>>FUNCTION>>>> (auto-generated)//
// <<<<FUNCTION<<<< (will be overwritten!!)