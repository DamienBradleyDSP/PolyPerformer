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
	Rectangle<float> bg(0,0,47,31);
	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.fillRect(bg);

	Path Ellipse3;
	Ellipse3.startNewSubPath(30.25,30.1913);
	Ellipse3.cubicTo(32.8237,28.7054,34.8351,26.4118,35.9724,23.6662);
	Ellipse3.cubicTo(37.1096,20.9206,37.3092,17.8765,36.54,15.0059);
	Ellipse3.cubicTo(35.7708,12.1354,34.076,9.59885,31.7183,7.78973);
	Ellipse3.cubicTo(29.3606,5.98061,26.4718,5.0,23.5,5.0);
	Ellipse3.cubicTo(20.5282,5.0,17.6394,5.98061,15.2817,7.78973);
	Ellipse3.cubicTo(12.924,9.59886,11.2292,12.1354,10.46,15.0059);
	Ellipse3.cubicTo(9.69084,17.8765,9.89036,20.9206,11.0276,23.6662);
	Ellipse3.cubicTo(12.1649,26.4118,14.1763,28.7054,16.75,30.1913);
	Ellipse3.lineTo(23.5,18.5);
	Ellipse3.lineTo(30.25,30.1913);
	Ellipse3.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.fillPath(Ellipse3);

	Path Ellipse4;
	Ellipse4.startNewSubPath(28.75,27.5933);
	Ellipse4.cubicTo(30.7517,26.4376,32.3162,24.6536,33.2007,22.5182);
	Ellipse4.cubicTo(34.0853,20.3827,34.2405,18.015,33.6422,15.7824);
	Ellipse4.cubicTo(33.044,13.5497,31.7258,11.5769,29.892,10.1698);
	Ellipse4.cubicTo(28.0582,8.76269,25.8114,8.0,23.5,8.0);
	Ellipse4.cubicTo(21.1886,8.0,18.9418,8.76269,17.108,10.1698);
	Ellipse4.cubicTo(15.2742,11.5769,13.956,13.5498,13.3578,15.7824);
	Ellipse4.cubicTo(12.7595,18.0151,12.9147,20.3827,13.7993,22.5182);
	Ellipse4.cubicTo(14.6838,24.6536,16.2483,26.4376,18.25,27.5933);
	Ellipse4.lineTo(23.5,18.5);
	Ellipse4.lineTo(28.75,27.5933);
	Ellipse4.closeSubPath();

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.fillPath(Ellipse4);

	Rectangle<float> Rectangle4(21.5,0.5,4,12);
	/*g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.fillRoundedRectangle(Rectangle4,2);
	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.drawRoundedRectangle(Rectangle4,2,1.0);*/

	// <<<<PAINT<<<< (will be overwritten!!)

	auto centrepoint = Ellipse4.getBounds().getCentre();
	auto transform = AffineTransform::rotation(toAngle, centrepoint.getX(), centrepoint.getY());
	//draggableElement = draggableElement.transformedBy(transform);

	Path p;
	p.addRoundedRectangle(Rectangle4, 2, 2);
	g.setColour(Colour::fromRGB(172, 102, 117));
	g.strokePath(p, PathStrokeType(1), transform);
	g.setColour(Colour::fromRGB(218, 132, 151));
	g.fillPath(p, transform);
}


// >>>>RESIZED>>>> (auto-generated)//
// <<<<RESIZED<<<< (will be overwritten!!)

// >>>>FUNCTION>>>> (auto-generated)//
// <<<<FUNCTION<<<< (will be overwritten!!)