/*
  ==============================================================================

	THIS CODE WAS AUTOMATICALLY GENERATED

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "polyModule.h"

//==============================================================================
polyModule::polyModule(AudioProcessorValueTreeState& parameters, juce::Button::Listener& p, int m)
	: unusedmember(0), 
	noteSelectorKeyboard(noteSelectorKeyState,MidiKeyboardComponent::Orientation::horizontalKeyboard),
	moduleNumber(m)

// >>>>INITIALISATION>>>> (auto-generated)//
, noteSelector1(parameters, moduleNumber)
, OnOffButton1(parameters)
, rhythmLoader1(parameters,p)
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

	moduleRelease = parameters.getParameter("moduleRelease" + juce::String(moduleNumber));
	auto sliderStart = moduleRelease->getNormalisableRange().start;
	auto sliderEnd = moduleRelease->getNormalisableRange().end;
	sustainSliderSlider1.setRange(sliderStart, sliderEnd);
	sustainSliderSlider1.onValueChange = [this]() {
		auto newValue = sustainSliderSlider1.getValue();
		auto parameterRange = moduleRelease->getNormalisableRange();
		auto mappedValue = parameterRange.convertTo0to1(newValue);
		moduleRelease->setValueNotifyingHost(mappedValue);
	};
	sustainSliderSlider1.setSkewFactor(0.3);
	sustainSliderSlider1.setValue(moduleRelease->getNormalisableRange().convertFrom0to1(moduleRelease->getValue()), dontSendNotification);

	addAndMakeVisible(noteSelectorKeyboard);
	noteSelectorKeyboard.setVisible(false);
	noteSelectorKeyState.addListener(&noteSelector1);
	noteSelector1.addListener(this);
	noteSelectorKeyboard.setColour(MidiKeyboardComponent::ColourIds::mouseOverKeyOverlayColourId, Colour::fromRGB(218, 132, 151).brighter(0.4));
	noteSelectorKeyboard.setColour(MidiKeyboardComponent::ColourIds::keyDownOverlayColourId, Colour::fromRGB(218, 132, 151));
	noteSelectorKeyboard.setColour(MidiKeyboardComponent::ColourIds::upDownButtonArrowColourId, Colour::fromRGB(218, 132, 151));

	rhythmLoader1.setName(juce::String(moduleNumber));

	moduleOnOff = parameters.getParameter("moduleOnOff" + juce::String(moduleNumber));
	OnOffButton1.setToggleState((bool)moduleOnOff->getValue(), dontSendNotification);
	OnOffButton1.onClick = [this]() {
		moduleOnOff->setValueNotifyingHost(OnOffButton1.getToggleState());
	};
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

void polyModule::setModuleName(juce::String presetName)
{
	rhythmLoader1.setModuleName(presetName);
}

void polyModule::updateStateInformation()
{
	noteSelector1.updateStateInformation();
	OnOffButton1.setToggleState((bool)moduleOnOff->getValue(), dontSendNotification);
	sustainSliderSlider1.setValue(moduleRelease->getNormalisableRange().convertFrom0to1(moduleRelease->getValue()), dontSendNotification);
	sustainSliderSlider1.setValue(moduleRelease->getNormalisableRange().convertFrom0to1(moduleRelease->getValue()), dontSendNotification);
}

void polyModule::buttonClicked(Button*)
{
	noteSelectorKeyboard.setVisible(!noteSelectorKeyboard.isVisible());
}

// >>>>FUNCTION>>>> (auto-generated)//
// <<<<FUNCTION<<<< (will be overwritten!!)