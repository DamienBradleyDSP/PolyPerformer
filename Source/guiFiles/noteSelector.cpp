/*
  ==============================================================================

	THIS CODE WAS AUTOMATICALLY GENERATED

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "noteSelector.h"

//==============================================================================

noteSelector::noteSelector(AudioProcessorValueTreeState& parameters, int m)
	: Button(String()), moduleNumber(m)
	// >>>>INITIALISATION>>>> (auto-generated)//
	// <<<<INITIALISATION<<<< (will be overwritten!!)   
{
	// >>>>CONSTRUCTOR>>>> (auto-generated)//
	addAndMakeVisible(noteDisplay1);
	noteDisplay1.setText(String("PLACEHOLDER"),dontSendNotification);
	noteDisplay1.setFont(Font(16, 0));
	noteDisplay1.setJustificationType(Justification::centred);
	noteDisplay1.setColour(Label::textColourId,Colour::fromRGB(218,132,151));
	noteDisplay1.setColour(Label::textWhenEditingColourId,Colour::fromRGB(218,132,151));
	// <<<<CONSTRUCTOR<<<< (will be overwritten!!)   

	noteDisplay1.setInterceptsMouseClicks(false,false);
	Font font;
	font.setHeight(20);
	noteDisplay1.setFont(font);
	noteDisplay1.setText(String("C#1"),dontSendNotification);

	// ENABLE THIS AFTER PARAMETERS MADE
	noteNumber = parameters.getParameter("moduleNoteNumber"+juce::String(moduleNumber));
	auto noteName = MidiMessage::getMidiNoteName(noteNumber->getCurrentValueAsText().getFloatValue(), true, true, 3);
	noteDisplay1.setText(noteName, dontSendNotification);

}

noteSelector::~noteSelector()
{
}

void noteSelector::updateStateInformation()
{
	auto noteName = MidiMessage::getMidiNoteName(noteNumber->getCurrentValueAsText().getFloatValue(), true, true, 3);
	noteDisplay1.setText(noteName, dontSendNotification);
	repaint();
}

void noteSelector::paintButton(Graphics &g, bool isMouseOverButton, bool isButtonDown)
{
	// >>>>PAINT>>>> (auto-generated)//
	Path path6;
	path6.startNewSubPath(33.45,1.0);
	path6.lineTo(9.55,1.0);
	path6.cubicTo(4.82797,1.0,1.0,4.82796,1.0,9.55);
	path6.lineTo(1.0,33.45);
	path6.cubicTo(1.0,38.172,4.82797,42.0,9.55,42.0);
	path6.lineTo(33.45,42.0);
	path6.cubicTo(38.172,42.0,42.0,38.172,42.0,33.45);
	path6.lineTo(42.0,9.55);
	path6.cubicTo(42.0,4.82796,38.172,1.0,33.45,1.0);
	path6.closeSubPath();

	g.setColour(Colour::fromRGB(0,0,0));
	g.setOpacity(0.25);
	g.fillPath(path6);

	Path Vector_2;
	Vector_2.startNewSubPath(32.45,0.0);
	Vector_2.lineTo(8.55,0.0);
	Vector_2.cubicTo(3.82797,0.0,0.0,3.82796,0.0,8.55);
	Vector_2.lineTo(0.0,32.45);
	Vector_2.cubicTo(0.0,37.172,3.82797,41.0,8.55,41.0);
	Vector_2.lineTo(32.45,41.0);
	Vector_2.cubicTo(37.172,41.0,41.0,37.172,41.0,32.45);
	Vector_2.lineTo(41.0,8.55);
	Vector_2.cubicTo(41.0,3.82796,37.172,0.0,32.45,0.0);
	Vector_2.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.fillPath(Vector_2);

	// <<<<PAINT<<<< (will be overwritten!!)

	if (isButtonDown)
	{
	}
	else if (isMouseOverButton)
	{
	}
	else
	{
	}
	
	// >>>>RESIZED>>>> (auto-generated)//
	noteDisplay1.setBounds(0,0,42,42);
	// <<<<RESIZED<<<< (will be overwritten!!)
}

void noteSelector::handleNoteOn(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
}

void noteSelector::handleNoteOff(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{

	triggerClick();

	noteNumber->setValueNotifyingHost(noteNumber->getValueForText(juce::String(midiNoteNumber)));
	auto noteName = MidiMessage::getMidiNoteName(noteNumber->getCurrentValueAsText().getFloatValue(), true, true, 3);
	noteDisplay1.setText(noteName, dontSendNotification);
}



// >>>>FUNCTION>>>> (auto-generated)//
// <<<<FUNCTION<<<< (will be overwritten!!)