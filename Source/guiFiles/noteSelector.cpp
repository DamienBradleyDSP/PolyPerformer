/*
  ==============================================================================

	THIS CODE WAS AUTOMATICALLY GENERATED

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "noteSelector.h"

//==============================================================================

noteSelector::noteSelector(AudioProcessorValueTreeState& parameters)
	: Button(String())
	// >>>>INITIALISATION>>>> (auto-generated)//
	// <<<<INITIALISATION<<<< (will be overwritten!!)   
{
	// >>>>CONSTRUCTOR>>>> (auto-generated)//
	addAndMakeVisible(noteDisplay1);
	noteDisplay1.setText(String("PLACEHOLDER"),dontSendNotification);
	noteDisplay1.setFont(Font(16, 0));
	noteDisplay1.setJustificationType(Justification::centred);
	noteDisplay1.setColour(Label::textColourId,Colour::fromRGB(196,196,196));
	noteDisplay1.setColour(Label::textWhenEditingColourId,Colour::fromRGB(196,196,196));
	// <<<<CONSTRUCTOR<<<< (will be overwritten!!)   
}

noteSelector::~noteSelector()
{
}

void noteSelector::paintButton(Graphics &g, bool isMouseOverButton, bool isButtonDown)
{
	// >>>>PAINT>>>> (auto-generated)//
	Path path5;
	path5.startNewSubPath(33.45,1.0);
	path5.lineTo(9.55,1.0);
	path5.cubicTo(4.82797,1.0,1.0,4.82796,1.0,9.55);
	path5.lineTo(1.0,33.45);
	path5.cubicTo(1.0,38.172,4.82797,42.0,9.55,42.0);
	path5.lineTo(33.45,42.0);
	path5.cubicTo(38.172,42.0,42.0,38.172,42.0,33.45);
	path5.lineTo(42.0,9.55);
	path5.cubicTo(42.0,4.82796,38.172,1.0,33.45,1.0);
	path5.closeSubPath();

	g.setColour(Colour::fromRGB(0,0,0));
	g.setOpacity(0.25);
	g.fillPath(path5);

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

	Path path11;
	path11.startNewSubPath(10.5285,22.8634);
	path11.lineTo(12.5135,23.081);
	path11.cubicTo(12.3858,24.2709,11.9244,25.2517,11.1292,26.0236);
	path11.cubicTo(10.3399,26.7898,9.30098,27.1728,8.0125,27.1728);
	path11.cubicTo(6.92716,27.1728,6.04496,26.9,5.3659,26.3545);
	path11.cubicTo(4.69264,25.8089,4.17319,25.0689,3.80754,24.1345);
	path11.cubicTo(3.44189,23.2,3.25906,22.1698,3.25906,21.0439);
	path11.cubicTo(3.25906,19.233,3.68856,17.7617,4.54754,16.6299);
	path11.cubicTo(5.40653,15.4924,6.58763,14.9236,8.09086,14.9236);
	path11.cubicTo(9.26906,14.9236,10.2499,15.2863,11.0335,16.0118);
	path11.cubicTo(11.817,16.7373,12.3103,17.7762,12.5135,19.1285);
	path11.lineTo(10.5285,19.3375);
	path11.cubicTo(10.1629,17.5441,9.35612,16.6474,8.10827,16.6474);
	path11.cubicTo(7.30732,16.6474,6.6834,17.0217,6.23649,17.7704);
	path11.cubicTo(5.79539,18.5133,5.57484,19.5929,5.57484,21.009);
	path11.cubicTo(5.57484,22.4484,5.8128,23.5367,6.28873,24.2738);
	path11.cubicTo(6.76465,25.0051,7.39438,25.3707,8.17792,25.3707);
	path11.cubicTo(8.80474,25.3707,9.33871,25.124,9.77981,24.6307);
	path11.cubicTo(10.2209,24.1374,10.4705,23.5483,10.5285,22.8634);
	path11.closeSubPath();
	path11.startNewSubPath(22.9258,18.3363);
	path11.lineTo(22.6298,20.0166);
	path11.lineTo(20.8973,20.0166);
	path11.lineTo(20.5752,21.8361);
	path11.lineTo(22.3076,21.8361);
	path11.lineTo(22.0116,23.5163);
	path11.lineTo(20.2705,23.5163);
	path11.lineTo(19.6523,26.99);
	path11.lineTo(18.033,26.99);
	path11.lineTo(18.6512,23.5163);
	path11.lineTo(16.762,23.5163);
	path11.lineTo(16.1438,26.99);
	path11.lineTo(14.5071,26.99);
	path11.lineTo(15.1253,23.4989);
	path11.lineTo(13.3405,23.4989);
	path11.lineTo(13.6365,21.8361);
	path11.lineTo(15.4474,21.8361);
	path11.lineTo(15.7695,20.0166);
	path11.lineTo(13.9587,20.0166);
	path11.lineTo(14.2634,18.3363);
	path11.lineTo(16.0655,18.3363);
	path11.lineTo(16.6401,15.1064);
	path11.lineTo(18.2594,15.1064);
	path11.lineTo(17.6848,18.3363);
	path11.lineTo(19.5566,18.3363);
	path11.lineTo(20.1312,15.1064);
	path11.lineTo(21.7505,15.1064);
	path11.lineTo(21.1672,18.3363);
	path11.lineTo(22.9258,18.3363);
	path11.closeSubPath();
	path11.startNewSubPath(19.2606,20.0166);
	path11.lineTo(17.3801,20.0166);
	path11.lineTo(17.0667,21.8361);
	path11.lineTo(18.9384,21.8361);
	path11.lineTo(19.2606,20.0166);
	path11.closeSubPath();
	path11.startNewSubPath(38.1437,26.99);
	path11.lineTo(29.046,26.99);
	path11.lineTo(29.046,25.2401);
	path11.lineTo(32.6242,25.2401);
	path11.lineTo(32.6242,17.7356);
	path11.cubicTo(31.4344,18.7745,30.3519,19.4884,29.3769,19.8773);
	path11.lineTo(29.3769,17.7356);
	path11.cubicTo(30.3693,17.3583,30.9904,17.0914,31.2399,16.9347);
	path11.cubicTo(31.4895,16.7721,31.8552,16.4761,32.3369,16.0466);
	path11.cubicTo(32.8186,15.6114,33.1581,15.2167,33.3555,14.8626);
	path11.lineTo(34.7832,14.8626);
	path11.lineTo(34.7832,25.2401);
	path11.lineTo(38.1437,25.2401);
	path11.lineTo(38.1437,26.99);
	path11.closeSubPath();

	g.setColour(Colour::fromRGB(0,0,0));
	g.setOpacity(0.25);
	g.fillPath(path11);

	Path Chash1_2;
	Chash1_2.startNewSubPath(10.0285,22.3634);
	Chash1_2.lineTo(12.0135,22.581);
	Chash1_2.cubicTo(11.8858,23.7709,11.4244,24.7517,10.6292,25.5236);
	Chash1_2.cubicTo(9.83989,26.2898,8.80098,26.6728,7.5125,26.6728);
	Chash1_2.cubicTo(6.42716,26.6728,5.54496,26.4,4.8659,25.8545);
	Chash1_2.cubicTo(4.19264,25.3089,3.67319,24.5689,3.30754,23.6345);
	Chash1_2.cubicTo(2.94189,22.7,2.75906,21.6698,2.75906,20.5439);
	Chash1_2.cubicTo(2.75906,18.733,3.18856,17.2617,4.04754,16.1299);
	Chash1_2.cubicTo(4.90653,14.9924,6.08763,14.4236,7.59086,14.4236);
	Chash1_2.cubicTo(8.76906,14.4236,9.74993,14.7863,10.5335,15.5118);
	Chash1_2.cubicTo(11.317,16.2373,11.8103,17.2762,12.0135,18.6285);
	Chash1_2.lineTo(10.0285,18.8375);
	Chash1_2.cubicTo(9.66287,17.0441,8.85612,16.1474,7.60827,16.1474);
	Chash1_2.cubicTo(6.80732,16.1474,6.1834,16.5217,5.73649,17.2704);
	Chash1_2.cubicTo(5.29539,18.0133,5.07484,19.0929,5.07484,20.509);
	Chash1_2.cubicTo(5.07484,21.9484,5.3128,23.0367,5.78873,23.7738);
	Chash1_2.cubicTo(6.26465,24.5051,6.89438,24.8707,7.67792,24.8707);
	Chash1_2.cubicTo(8.30474,24.8707,8.83871,24.624,9.27981,24.1307);
	Chash1_2.cubicTo(9.72091,23.6374,9.97048,23.0483,10.0285,22.3634);
	Chash1_2.closeSubPath();
	Chash1_2.startNewSubPath(22.4258,17.8363);
	Chash1_2.lineTo(22.1298,19.5166);
	Chash1_2.lineTo(20.3973,19.5166);
	Chash1_2.lineTo(20.0752,21.3361);
	Chash1_2.lineTo(21.8076,21.3361);
	Chash1_2.lineTo(21.5116,23.0163);
	Chash1_2.lineTo(19.7705,23.0163);
	Chash1_2.lineTo(19.1523,26.49);
	Chash1_2.lineTo(17.533,26.49);
	Chash1_2.lineTo(18.1512,23.0163);
	Chash1_2.lineTo(16.262,23.0163);
	Chash1_2.lineTo(15.6438,26.49);
	Chash1_2.lineTo(14.0071,26.49);
	Chash1_2.lineTo(14.6253,22.9989);
	Chash1_2.lineTo(12.8405,22.9989);
	Chash1_2.lineTo(13.1365,21.3361);
	Chash1_2.lineTo(14.9474,21.3361);
	Chash1_2.lineTo(15.2695,19.5166);
	Chash1_2.lineTo(13.4587,19.5166);
	Chash1_2.lineTo(13.7634,17.8363);
	Chash1_2.lineTo(15.5655,17.8363);
	Chash1_2.lineTo(16.1401,14.6064);
	Chash1_2.lineTo(17.7594,14.6064);
	Chash1_2.lineTo(17.1848,17.8363);
	Chash1_2.lineTo(19.0566,17.8363);
	Chash1_2.lineTo(19.6312,14.6064);
	Chash1_2.lineTo(21.2505,14.6064);
	Chash1_2.lineTo(20.6672,17.8363);
	Chash1_2.lineTo(22.4258,17.8363);
	Chash1_2.closeSubPath();
	Chash1_2.startNewSubPath(18.7606,19.5166);
	Chash1_2.lineTo(16.8801,19.5166);
	Chash1_2.lineTo(16.5667,21.3361);
	Chash1_2.lineTo(18.4384,21.3361);
	Chash1_2.lineTo(18.7606,19.5166);
	Chash1_2.closeSubPath();
	Chash1_2.startNewSubPath(37.6437,26.49);
	Chash1_2.lineTo(28.546,26.49);
	Chash1_2.lineTo(28.546,24.7401);
	Chash1_2.lineTo(32.1242,24.7401);
	Chash1_2.lineTo(32.1242,17.2356);
	Chash1_2.cubicTo(30.9344,18.2745,29.8519,18.9884,28.8769,19.3773);
	Chash1_2.lineTo(28.8769,17.2356);
	Chash1_2.cubicTo(29.8693,16.8583,30.4904,16.5914,30.7399,16.4347);
	Chash1_2.cubicTo(30.9895,16.2721,31.3552,15.9761,31.8369,15.5466);
	Chash1_2.cubicTo(32.3186,15.1114,32.6581,14.7167,32.8555,14.3626);
	Chash1_2.lineTo(34.2832,14.3626);
	Chash1_2.lineTo(34.2832,24.7401);
	Chash1_2.lineTo(37.6437,24.7401);
	Chash1_2.lineTo(37.6437,26.49);
	Chash1_2.closeSubPath();

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.fillPath(Chash1_2);

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
	noteDisplay1.setBounds(0, 0, 42, 42);
	// <<<<RESIZED<<<< (will be overwritten!!)
}



// >>>>FUNCTION>>>> (auto-generated)//
// <<<<FUNCTION<<<< (will be overwritten!!)