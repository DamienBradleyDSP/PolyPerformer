/*
  ==============================================================================

	THIS CODE WAS AUTOMATICALLY GENERATED

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "polyModule.h"

//==============================================================================
polyModule::polyModule(AudioProcessorValueTreeState& parameters)
	: unusedmember(0), noteSelectorKeyboard(noteSelectorKeyState,MidiKeyboardComponent::Orientation::horizontalKeyboard)
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

	addAndMakeVisible(noteSelectorKeyboard);
	noteSelectorKeyboard.setVisible(false);
	noteSelectorKeyState.addListener(&noteSelector1);
	noteSelector1.addListener(this);
	noteSelectorKeyboard.setColour(MidiKeyboardComponent::ColourIds::mouseOverKeyOverlayColourId, Colour::fromRGB(218, 132, 151).brighter(0.4));
	noteSelectorKeyboard.setColour(MidiKeyboardComponent::ColourIds::keyDownOverlayColourId, Colour::fromRGB(218, 132, 151));
	noteSelectorKeyboard.setColour(MidiKeyboardComponent::ColourIds::upDownButtonArrowColourId, Colour::fromRGB(218, 132, 151));
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
	sustainSliderSlider1.setBounds(312,8,47,36);
	noteSelector1.setBounds(49,3,42,42);
	OnOffButton1.setBounds(0,0,48,48);
	rhythmLoader1.setBounds(109,4,201,40);
	// <<<<RESIZED<<<< (will be overwritten!!)

	noteSelectorKeyboard.setBounds(rhythmLoader1.getBounds());
}

void polyModule::buttonClicked(Button*)
{
	noteSelectorKeyboard.setVisible(!noteSelectorKeyboard.isVisible());
}

// >>>>FUNCTION>>>> (auto-generated)//
// <<<<FUNCTION<<<< (will be overwritten!!)