/*
  ==============================================================================

	THIS CODE WAS AUTOMATICALLY GENERATED

  ==============================================================================
*/

#include "OnOffButton.h"


OnOffButton::OnOffButton(AudioProcessorValueTreeState& parameters)
	: unusedmember(0)
	// >>>>INITIALISATION>>>> (auto-generated)//
	// <<<<INITIALISATION<<<< (will be overwritten!!)   
{
	// >>>>CONSTRUCTOR>>>> (auto-generated)//
	// <<<<CONSTRUCTOR<<<< (will be overwritten!!)   
}

OnOffButton::~OnOffButton()
{
}

void OnOffButton::paintButton(Graphics &g, bool isMouseOverButton, bool isButtonDown)
{
	// >>>>PAINT>>>> (auto-generated)//
	// <<<<PAINT<<<< (will be overwritten!!)

	if (getToggleState())
	{
		if (isMouseOverButton)
		{
			toggleOnHover(g);
		}
		else
		{
			toggleOn(g);
		}
	}
	else
	{
		if (isMouseOverButton)
		{
			toggleOffHover(g);
		}
		else
		{
			toggleOff(g);
		}
	}

}

// >>>>RESIZED>>>> (auto-generated)//
// <<<<RESIZED<<<< (will be overwritten!!)

// >>>>FUNCTION>>>> (auto-generated)//
void OnOffButton::toggleOff(Graphics &g){
	Path Vector;
	Vector.startNewSubPath(23.5,34.25);
	Vector.cubicTo(29.4371,34.25,34.25,29.4371,34.25,23.5);
	Vector.cubicTo(34.25,17.5629,29.4371,12.75,23.5,12.75);
	Vector.cubicTo(17.5629,12.75,12.75,17.5629,12.75,23.5);
	Vector.cubicTo(12.75,29.4371,17.5629,34.25,23.5,34.25);
	Vector.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.strokePath(Vector,juce::PathStrokeType(3));

}
void OnOffButton::toggleOffHover(Graphics &g){
	Path Vector_2;
	Vector_2.startNewSubPath(23.5,34.25);
	Vector_2.cubicTo(29.4371,34.25,34.25,29.4371,34.25,23.5);
	Vector_2.cubicTo(34.25,17.5629,29.4371,12.75,23.5,12.75);
	Vector_2.cubicTo(17.5629,12.75,12.75,17.5629,12.75,23.5);
	Vector_2.cubicTo(12.75,29.4371,17.5629,34.25,23.5,34.25);
	Vector_2.closeSubPath();

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.fillPath(Vector_2);
	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.strokePath(Vector_2,juce::PathStrokeType(3));

	Rectangle<float> Ellipse5(21.0,21.0,5.0,5.0);
	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.fillEllipse(Ellipse5);

}
void OnOffButton::toggleOnHover(Graphics &g){
	Path Vector_3;
	Vector_3.startNewSubPath(23.5,34.25);
	Vector_3.cubicTo(29.4371,34.25,34.25,29.4371,34.25,23.5);
	Vector_3.cubicTo(34.25,17.5629,29.4371,12.75,23.5,12.75);
	Vector_3.cubicTo(17.5629,12.75,12.75,17.5629,12.75,23.5);
	Vector_3.cubicTo(12.75,29.4371,17.5629,34.25,23.5,34.25);
	Vector_3.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.fillPath(Vector_3);
	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.strokePath(Vector_3,juce::PathStrokeType(3));

	Path Vector_4;
	Vector_4.startNewSubPath(23.6444,31.2889);
	Vector_4.cubicTo(27.8664,31.2889,31.2889,27.8664,31.2889,23.6444);
	Vector_4.cubicTo(31.2889,19.4225,27.8664,16.0,23.6444,16.0);
	Vector_4.cubicTo(19.4225,16.0,16.0,19.4225,16.0,23.6444);
	Vector_4.cubicTo(16.0,27.8664,19.4225,31.2889,23.6444,31.2889);
	Vector_4.closeSubPath();

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.strokePath(Vector_4,juce::PathStrokeType(2));

}
void OnOffButton::toggleOn(Graphics &g){
	Path Vector_5;
	Vector_5.startNewSubPath(23.5,34.25);
	Vector_5.cubicTo(29.4371,34.25,34.25,29.4371,34.25,23.5);
	Vector_5.cubicTo(34.25,17.5629,29.4371,12.75,23.5,12.75);
	Vector_5.cubicTo(17.5629,12.75,12.75,17.5629,12.75,23.5);
	Vector_5.cubicTo(12.75,29.4371,17.5629,34.25,23.5,34.25);
	Vector_5.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.fillPath(Vector_5);
	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.strokePath(Vector_5,juce::PathStrokeType(3));

	Path Vector_6;
	Vector_6.startNewSubPath(23.6444,31.2889);
	Vector_6.cubicTo(27.8664,31.2889,31.2889,27.8664,31.2889,23.6444);
	Vector_6.cubicTo(31.2889,19.4225,27.8664,16.0,23.6444,16.0);
	Vector_6.cubicTo(19.4225,16.0,16.0,19.4225,16.0,23.6444);
	Vector_6.cubicTo(16.0,27.8664,19.4225,31.2889,23.6444,31.2889);
	Vector_6.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.fillPath(Vector_6);
	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.strokePath(Vector_6,juce::PathStrokeType(1.0));

}
// <<<<FUNCTION<<<< (will be overwritten!!)

