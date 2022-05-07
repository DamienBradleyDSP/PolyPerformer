/*
  ==============================================================================

	THIS CODE WAS AUTOMATICALLY GENERATED

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "sustainSlider.h"

//==============================================================================

// >>>>INITIALISATION>>>> (auto-generated)//
// <<<<INITIALISATION<<<< (will be overwritten!!)   

// >>>>CONSTRUCTOR>>>> (auto-generated)//
// <<<<CONSTRUCTOR<<<< (will be overwritten!!)   


void sustainSlider::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
	auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);
	auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
	auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	auto lineW = jmin(8.0f, radius * 0.5f);
	auto arcRadius = radius - lineW * 0.5f;

	// >>>>PAINT>>>> (auto-generated)//
	Path Ellipse3;
	Ellipse3.startNewSubPath(20.25,30.1913);
	Ellipse3.cubicTo(22.8237,28.7054,24.8351,26.4118,25.9724,23.6662);
	Ellipse3.cubicTo(27.1096,20.9206,27.3092,17.8765,26.54,15.0059);
	Ellipse3.cubicTo(25.7708,12.1354,24.076,9.59885,21.7183,7.78973);
	Ellipse3.cubicTo(19.3606,5.98061,16.4718,5.0,13.5,5.0);
	Ellipse3.cubicTo(10.5282,5.0,7.63942,5.98061,5.28172,7.78973);
	Ellipse3.cubicTo(2.92402,9.59886,1.22916,12.1354,0.460001,15.0059);
	Ellipse3.cubicTo(-0.30916,17.8765,-0.109637,20.9206,1.02763,23.6662);
	Ellipse3.cubicTo(2.16489,26.4118,4.17634,28.7054,6.75,30.1913);
	Ellipse3.lineTo(13.5,18.5);
	Ellipse3.lineTo(20.25,30.1913);
	Ellipse3.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.fillPath(Ellipse3);

	Path Ellipse4;
	Ellipse4.startNewSubPath(18.75,27.5933);
	Ellipse4.cubicTo(20.7517,26.4376,22.3162,24.6536,23.2007,22.5182);
	Ellipse4.cubicTo(24.0853,20.3827,24.2405,18.0151,23.6422,15.7824);
	Ellipse4.cubicTo(23.044,13.5497,21.7258,11.5769,19.892,10.1698);
	Ellipse4.cubicTo(18.0582,8.76269,15.8114,8.0,13.5,8.0);
	Ellipse4.cubicTo(11.1886,8.0,8.94177,8.76269,7.108,10.1698);
	Ellipse4.cubicTo(5.27424,11.5769,3.95602,13.5498,3.35778,15.7824);
	Ellipse4.cubicTo(2.75954,18.0151,2.91473,20.3827,3.79927,22.5182);
	Ellipse4.cubicTo(4.6838,24.6536,6.24826,26.4376,8.25,27.5933);
	Ellipse4.lineTo(13.5,18.5);
	Ellipse4.lineTo(18.75,27.5933);
	Ellipse4.closeSubPath();

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.fillPath(Ellipse4);

	Rectangle<float> Rectangle4(11.5,0.5,4,12);
	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.fillRoundedRectangle(Rectangle4,2);
	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.drawRoundedRectangle(Rectangle4,2,1.0);

	// <<<<PAINT<<<< (will be overwritten!!)
}


// >>>>RESIZED>>>> (auto-generated)//
// <<<<RESIZED<<<< (will be overwritten!!)

// >>>>FUNCTION>>>> (auto-generated)//
// <<<<FUNCTION<<<< (will be overwritten!!)