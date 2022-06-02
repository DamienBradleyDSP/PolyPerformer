/*
  ==============================================================================

	THIS CODE WAS AUTOMATICALLY GENERATED

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "rhythmLoader.h"

//==============================================================================
rhythmLoader::rhythmLoader(AudioProcessorValueTreeState& parameters, juce::Button::Listener& p)
	: unusedmember(0), Button(String(0))
// >>>>INITIALISATION>>>> (auto-generated)//
// <<<<INITIALISATION<<<< (will be overwritten!!)   
{
	// >>>>CONSTRUCTOR>>>> (auto-generated)//
	addAndMakeVisible(fileName1);
	fileName1.setText(String("<empty>"),dontSendNotification);
	fileName1.setFont(Font(16, 0));
	fileName1.setJustificationType(Justification::centred);
	fileName1.setColour(Label::textColourId,Colour::fromRGB(218,132,151));
	fileName1.setColour(Label::textWhenEditingColourId,Colour::fromRGB(218,132,151));
	// <<<<CONSTRUCTOR<<<< (will be overwritten!!)   
	fileName1.setInterceptsMouseClicks(false, false);

	addListener(&p); // Change on click to processor
}

rhythmLoader::~rhythmLoader()
{
}

void rhythmLoader::paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown)
{
	// >>>>PAINT>>>> (auto-generated)//
	Rectangle<float> Rectangle1(0, 0, 201, 40);
	g.setColour(Colour::fromRGB(172, 102, 117));
	g.setOpacity(1.0);
	g.fillRoundedRectangle(Rectangle1, 10);

	Rectangle<float> Rectangle2(2, 2, 197, 36);
	g.setColour(Colour::fromRGB(183, 110, 126));
	g.setOpacity(1.0);
	g.fillRoundedRectangle(Rectangle2, 10);

	// <<<<PAINT<<<< (will be overwritten!!)

	// >>>>RESIZED>>>> (auto-generated)//
	fileName1.setBounds(0, 0, 201, 40);
	// <<<<RESIZED<<<< (will be overwritten!!)
}

// >>>>FUNCTION>>>> (auto-generated)//
// <<<<FUNCTION<<<< (will be overwritten!!)