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

		}
		else
		{

		}
	}
	else
	{
		if (isMouseOverButton)
		{

		}
		else
		{

		}
	}

}

// >>>>RESIZED>>>> (auto-generated)//
// <<<<RESIZED<<<< (will be overwritten!!)

// >>>>FUNCTION>>>> (auto-generated)//
void OnOffButton::toggleOff(Graphics &g){
	Path path8;
	path8.startNewSubPath(24.5,35.25);
	path8.cubicTo(30.4371,35.25,35.25,30.4371,35.25,24.5);
	path8.cubicTo(35.25,18.5629,30.4371,13.75,24.5,13.75);
	path8.cubicTo(18.5629,13.75,13.75,18.5629,13.75,24.5);
	path8.cubicTo(13.75,30.4371,18.5629,35.25,24.5,35.25);
	path8.closeSubPath();

	g.setColour(Colour::fromRGB(0,0,0));
	g.setOpacity(0.25);
	g.strokePath(path8,juce::PathStrokeType(3));

	Path Vector_2;
	Vector_2.startNewSubPath(23.5,34.25);
	Vector_2.cubicTo(29.4371,34.25,34.25,29.4371,34.25,23.5);
	Vector_2.cubicTo(34.25,17.5629,29.4371,12.75,23.5,12.75);
	Vector_2.cubicTo(17.5629,12.75,12.75,17.5629,12.75,23.5);
	Vector_2.cubicTo(12.75,29.4371,17.5629,34.25,23.5,34.25);
	Vector_2.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.strokePath(Vector_2,juce::PathStrokeType(3));

}
void OnOffButton::toggleHover(Graphics &g){
	Path leftEqualErrorCharPathrightEqualErrorChar;
	leftEqualErrorCharPathrightEqualErrorChar.startNewSubPath(23.9889,34.8091);
	leftEqualErrorCharPathrightEqualErrorChar.cubicTo(29.9647,34.8091,34.8091,29.9647,34.8091,23.9889);
	leftEqualErrorCharPathrightEqualErrorChar.cubicTo(34.8091,18.013,29.9647,13.1687,23.9889,13.1687);
	leftEqualErrorCharPathrightEqualErrorChar.cubicTo(18.013,13.1687,13.1687,18.013,13.1687,23.9889);
	leftEqualErrorCharPathrightEqualErrorChar.cubicTo(13.1687,29.9647,18.013,34.8091,23.9889,34.8091);
	leftEqualErrorCharPathrightEqualErrorChar.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.fillPath(leftEqualErrorCharPathrightEqualErrorChar);

	Path Vector_3;
	Vector_3.startNewSubPath(23.9889,34.9778);
	Vector_3.cubicTo(30.0579,34.9778,34.9778,30.0579,34.9778,23.9889);
	Vector_3.cubicTo(34.9778,17.9199,30.0579,13.0,23.9889,13.0);
	Vector_3.cubicTo(17.9199,13.0,13.0,17.9199,13.0,23.9889);
	Vector_3.cubicTo(13.0,30.0579,17.9199,34.9778,23.9889,34.9778);
	Vector_3.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.strokePath(Vector_3,juce::PathStrokeType(3));

}
void OnOffButton::toggleOn(Graphics &g){
	Path leftEqualErrorCharPathrightEqualErrorChar_2;
	leftEqualErrorCharPathrightEqualErrorChar_2.startNewSubPath(23.5,34.085);
	leftEqualErrorCharPathrightEqualErrorChar_2.cubicTo(29.3459,34.085,34.085,29.3459,34.085,23.5);
	leftEqualErrorCharPathrightEqualErrorChar_2.cubicTo(34.085,17.6541,29.3459,12.915,23.5,12.915);
	leftEqualErrorCharPathrightEqualErrorChar_2.cubicTo(17.6541,12.915,12.915,17.6541,12.915,23.5);
	leftEqualErrorCharPathrightEqualErrorChar_2.cubicTo(12.915,29.3459,17.6541,34.085,23.5,34.085);
	leftEqualErrorCharPathrightEqualErrorChar_2.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.fillPath(leftEqualErrorCharPathrightEqualErrorChar_2);

	Path myVect;
	myVect.startNewSubPath(24.5,35.25);
	myVect.cubicTo(30.4371,35.25,35.25,30.4371,35.25,24.5);
	myVect.cubicTo(35.25,18.5629,30.4371,13.75,24.5,13.75);
	myVect.cubicTo(18.5629,13.75,13.75,18.5629,13.75,24.5);
	myVect.cubicTo(13.75,30.4371,18.5629,35.25,24.5,35.25);
	myVect.closeSubPath();

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(0.41);
	g.fillPath(myVect);
	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(0.41);
	g.strokePath(myVect,juce::PathStrokeType(3));

	Path Vector_4;
	Vector_4.startNewSubPath(23.5,34.25);
	Vector_4.cubicTo(29.4371,34.25,34.25,29.4371,34.25,23.5);
	Vector_4.cubicTo(34.25,17.5629,29.4371,12.75,23.5,12.75);
	Vector_4.cubicTo(17.5629,12.75,12.75,17.5629,12.75,23.5);
	Vector_4.cubicTo(12.75,29.4371,17.5629,34.25,23.5,34.25);
	Vector_4.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.strokePath(Vector_4,juce::PathStrokeType(3));

}
void OnOffButton::toggleOnClicked(Graphics &g){
	Path path31;
	path31.startNewSubPath(24.5,35.25);
	path31.cubicTo(30.4371,35.25,35.25,30.4371,35.25,24.5);
	path31.cubicTo(35.25,18.5629,30.4371,13.75,24.5,13.75);
	path31.cubicTo(18.5629,13.75,13.75,18.5629,13.75,24.5);
	path31.cubicTo(13.75,30.4371,18.5629,35.25,24.5,35.25);
	path31.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(0.25);
	g.strokePath(path31,juce::PathStrokeType(3));

	Path Vector_6;
	Vector_6.startNewSubPath(23.5,34.25);
	Vector_6.cubicTo(29.4371,34.25,34.25,29.4371,34.25,23.5);
	Vector_6.cubicTo(34.25,17.5629,29.4371,12.75,23.5,12.75);
	Vector_6.cubicTo(17.5629,12.75,12.75,17.5629,12.75,23.5);
	Vector_6.cubicTo(12.75,29.4371,17.5629,34.25,23.5,34.25);
	Vector_6.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.strokePath(Vector_6,juce::PathStrokeType(3));

	Path leftEqualErrorCharPathrightEqualErrorChar_3;
	leftEqualErrorCharPathrightEqualErrorChar_3.startNewSubPath(23.5,34.085);
	leftEqualErrorCharPathrightEqualErrorChar_3.cubicTo(29.3459,34.085,34.085,29.3459,34.085,23.5);
	leftEqualErrorCharPathrightEqualErrorChar_3.cubicTo(34.085,17.6541,29.3459,12.915,23.5,12.915);
	leftEqualErrorCharPathrightEqualErrorChar_3.cubicTo(17.6541,12.915,12.915,17.6541,12.915,23.5);
	leftEqualErrorCharPathrightEqualErrorChar_3.cubicTo(12.915,29.3459,17.6541,34.085,23.5,34.085);
	leftEqualErrorCharPathrightEqualErrorChar_3.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.fillPath(leftEqualErrorCharPathrightEqualErrorChar_3);

}
// <<<<FUNCTION<<<< (will be overwritten!!)

