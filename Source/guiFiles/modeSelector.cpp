/*
  ==============================================================================

	THIS CODE WAS AUTOMATICALLY GENERATED

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "modeSelector.h"

//==============================================================================

// >>>>INITIALISATION>>>> (auto-generated)//

// <<<<INITIALISATION<<<< (will be overwritten!!)   

// >>>>CONSTRUCTOR>>>> (auto-generated)//
// <<<<CONSTRUCTOR<<<< (will be overwritten!!)   


void modeSelector::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
	auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);
	auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
	auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	auto lineW = jmin(8.0f, radius * 0.5f);
	auto arcRadius = radius - lineW * 0.5f;

	// >>>>PAINT>>>> (auto-generated)//
	Path path3;
	path3.startNewSubPath(104.0,117.0);
	path3.cubicTo(104.0,162.287,67.2873,199.0,22.0,199.0);
	path3.cubicTo(-23.2873,199.0,-60.0,162.287,-60.0,117.0);
	path3.cubicTo(-60.0,71.7127,-23.2873,35.0,22.0,35.0);
	path3.cubicTo(67.2873,35.0,104.0,71.7127,104.0,117.0);
	path3.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.fillPath(path3);

	Path path5;
	path5.startNewSubPath(-110.0,0.0);
	path5.lineTo(22.0,0.0);
	path5.lineTo(22.0,233.0);
	path5.lineTo(-110.0,233.0);
	path5.lineTo(-110.0,0.0);
	path5.closeSubPath();

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.fillPath(path5);

	Path Line1;
	Line1.startNewSubPath(23.5,35);
	Line1.lineTo(23.5,110);

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.strokePath(Line1,juce::PathStrokeType(3));

	Path Line2;
	Line2.startNewSubPath(23.5,124);
	Line2.lineTo(23.5,199);

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.strokePath(Line2,juce::PathStrokeType(3));

	Path Line3;
	Line3.startNewSubPath(28.1925,121.071);
	Line3.lineTo(95.9365,160.183);

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.strokePath(Line3,juce::PathStrokeType(3));

	Path Line4;
	Line4.startNewSubPath(28.0804,113.189);
	Line4.lineTo(96.3066,73.7987);

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.strokePath(Line4,juce::PathStrokeType(3));

	/*Path Arrow1;
	Arrow1.startNewSubPath(22.0,29.2265);
	Arrow1.lineTo(16.2265,35.0);
	Arrow1.lineTo(22.0,40.7735);
	Arrow1.lineTo(27.7735,35.0);
	Arrow1.lineTo(22.0,29.2265);
	Arrow1.closeSubPath();
	Arrow1.startNewSubPath(23.0,109.0);
	Arrow1.lineTo(23.0,35.0);
	Arrow1.lineTo(21.0,35.0);
	Arrow1.lineTo(21.0,109.0);
	Arrow1.lineTo(23.0,109.0);
	Arrow1.closeSubPath();

	g.setColour(Colour::fromRGB(126,77,88));
	g.setOpacity(1.0);
	g.fillPath(Arrow1);

	Rectangle<float> Ellipse2(14.0,109.0,16.0,16.0);
	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.fillEllipse(Ellipse2);
	*/

	Path unknown13;
	unknown13.startNewSubPath(32.7861,45.0);
	unknown13.lineTo(27.6836,45.0);
	unknown13.lineTo(27.6836,44.0186);
	unknown13.lineTo(29.6904,44.0186);
	unknown13.lineTo(29.6904,39.8096);
	unknown13.cubicTo(29.0231,40.3923,28.416,40.7926,27.8691,41.0107);
	unknown13.lineTo(27.8691,39.8096);
	unknown13.cubicTo(28.4258,39.598,28.7741,39.4482,28.9141,39.3604);
	unknown13.cubicTo(29.054,39.2692,29.2591,39.1032,29.5293,38.8623);
	unknown13.cubicTo(29.7995,38.6182,29.9899,38.3968,30.1006,38.1982);
	unknown13.lineTo(30.9014,38.1982);
	unknown13.lineTo(30.9014,44.0186);
	unknown13.lineTo(32.7861,44.0186);
	unknown13.lineTo(32.7861,45.0);
	unknown13.closeSubPath();

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.fillPath(unknown13);

	Path unknown15;
	unknown15.startNewSubPath(93.332,88.96);
	unknown15.lineTo(93.332,90.0);
	unknown15.lineTo(88.4199,90.0);
	unknown15.lineTo(88.4199,88.833);
	unknown15.lineTo(90.4609,87.4756);
	unknown15.cubicTo(91.0957,87.0524,91.5221,86.6781,91.7402,86.3525);
	unknown15.cubicTo(91.9583,86.0238,92.0674,85.7227,92.0674,85.4492);
	unknown15.cubicTo(92.0674,85.1204,91.9583,84.8438,91.7402,84.6191);
	unknown15.cubicTo(91.5221,84.3945,91.2389,84.2822,90.8906,84.2822);
	unknown15.cubicTo(90.1289,84.2822,89.6911,84.7461,89.5771,85.6738);
	unknown15.lineTo(88.4199,85.3857);
	unknown15.cubicTo(88.5078,84.7933,88.7699,84.2871,89.2061,83.8672);
	unknown15.cubicTo(89.6455,83.444,90.2201,83.2324,90.9297,83.2324);
	unknown15.cubicTo(91.6654,83.2324,92.2529,83.4424,92.6924,83.8623);
	unknown15.cubicTo(93.1318,84.279,93.3516,84.8096,93.3516,85.4541);
	unknown15.cubicTo(93.3516,86.0238,93.1562,86.5332,92.7656,86.9824);
	unknown15.cubicTo(92.375,87.4284,91.4066,88.0876,89.8604,88.96);
	unknown15.lineTo(93.332,88.96);
	unknown15.closeSubPath();

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.fillPath(unknown15);

	Path unknown17;
	unknown17.startNewSubPath(82.1045,162.056);
	unknown17.lineTo(82.1045,161.108);
	unknown17.lineTo(82.7148,161.108);
	unknown17.cubicTo(83.0794,161.108,83.3838,161.027,83.6279,160.864);
	unknown17.cubicTo(83.8721,160.701,83.9941,160.459,83.9941,160.137);
	unknown17.cubicTo(83.9941,159.821,83.89,159.583,83.6816,159.424);
	unknown17.cubicTo(83.4766,159.264,83.2113,159.185,82.8857,159.185);
	unknown17.cubicTo(82.2282,159.185,81.7806,159.507,81.543,160.151);
	unknown17.lineTo(80.4443,159.961);
	unknown17.cubicTo(80.568,159.453,80.8529,159.038,81.2988,158.716);
	unknown17.cubicTo(81.748,158.394,82.2884,158.232,82.9199,158.232);
	unknown17.cubicTo(83.5482,158.232,84.0837,158.395,84.5264,158.721);
	unknown17.cubicTo(84.9723,159.043,85.1953,159.476,85.1953,160.02);
	unknown17.cubicTo(85.1953,160.423,85.0749,160.768,84.834,161.055);
	unknown17.cubicTo(84.5964,161.341,84.3018,161.497,83.9502,161.523);
	unknown17.cubicTo(84.3864,161.589,84.7363,161.769,85.0,162.065);
	unknown17.cubicTo(85.2669,162.362,85.4004,162.718,85.4004,163.135);
	unknown17.cubicTo(85.4004,163.708,85.1693,164.18,84.707,164.551);
	unknown17.cubicTo(84.248,164.919,83.6361,165.103,82.8711,165.103);
	unknown17.cubicTo(82.1647,165.103,81.5804,164.924,81.1182,164.565);
	unknown17.cubicTo(80.6592,164.204,80.3695,163.791,80.249,163.325);
	unknown17.lineTo(81.3867,163.047);
	unknown17.cubicTo(81.6146,163.789,82.1061,164.16,82.8613,164.16);
	unknown17.cubicTo(83.252,164.16,83.5661,164.061,83.8037,163.862);
	unknown17.cubicTo(84.0446,163.66,84.165,163.418,84.165,163.135);
	unknown17.cubicTo(84.165,162.848,84.0609,162.598,83.8525,162.383);
	unknown17.cubicTo(83.6475,162.165,83.3366,162.056,82.9199,162.056);
	unknown17.lineTo(82.1045,162.056);
	unknown17.closeSubPath();

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.fillPath(unknown17);

	Path unknown19;
	unknown19.startNewSubPath(31.5312,194.0);
	unknown19.lineTo(30.2959,194.0);
	unknown19.lineTo(30.2959,192.486);
	unknown19.lineTo(27.3369,192.486);
	unknown19.lineTo(27.3369,191.607);
	unknown19.lineTo(30.2959,187.198);
	unknown19.lineTo(31.5312,187.198);
	unknown19.lineTo(31.5312,191.461);
	unknown19.lineTo(32.5322,191.461);
	unknown19.lineTo(32.5322,192.486);
	unknown19.lineTo(31.5312,192.486);
	unknown19.lineTo(31.5312,194.0);
	unknown19.closeSubPath();
	unknown19.startNewSubPath(30.3838,188.453);
	unknown19.lineTo(28.4941,191.461);
	unknown19.lineTo(30.2959,191.461);
	unknown19.lineTo(30.2959,189.62);
	unknown19.cubicTo(30.2959,189.425,30.3057,189.249,30.3252,189.093);
	unknown19.lineTo(30.3838,188.453);
	unknown19.closeSubPath();

	g.setColour(Colour::fromRGB(218,132,151));
	g.setOpacity(1.0);
	g.fillPath(unknown19);

	Path modeselect;
	modeselect.startNewSubPath(12.0,147.679);
	modeselect.lineTo(12.0,149.759);
	modeselect.lineTo(6.52397,149.759);
	modeselect.cubicTo(5.38639,149.759,4.81761,150.264,4.81761,151.274);
	modeselect.cubicTo(4.81761,151.86,5.03235,152.331,5.46184,152.685);
	modeselect.cubicTo(5.89134,153.033,6.53267,153.207,7.38586,153.207);
	modeselect.lineTo(12.0,153.207);
	modeselect.lineTo(12.0,155.314);
	modeselect.lineTo(6.52397,155.314);
	modeselect.cubicTo(5.36898,155.314,4.79149,155.787,4.79149,156.733);
	modeselect.cubicTo(4.79149,157.308,5.02365,157.792,5.48796,158.187);
	modeselect.cubicTo(5.95228,158.576,6.58491,158.77,7.38586,158.77);
	modeselect.lineTo(12.0,158.77);
	modeselect.lineTo(12.0,160.816);
	modeselect.lineTo(3.20701,160.816);
	modeselect.lineTo(3.20701,158.892);
	modeselect.lineTo(5.07878,158.892);
	modeselect.cubicTo(3.70905,158.265,3.02418,157.287,3.02418,155.958);
	modeselect.cubicTo(3.02418,154.664,3.70905,153.822,5.07878,153.433);
	modeselect.cubicTo(3.70905,152.725,3.02418,151.747,3.02418,150.499);
	modeselect.cubicTo(3.02418,149.652,3.28826,148.97,3.81642,148.454);
	modeselect.cubicTo(4.34458,147.937,5.00043,147.679,5.78396,147.679);
	modeselect.lineTo(12.0,147.679);
	modeselect.closeSubPath();
	modeselect.startNewSubPath(12.1828,141.854);
	modeselect.cubicTo(12.1828,143.155,11.7156,144.147,10.7812,144.832);
	modeselect.cubicTo(9.84673,145.517,8.7759,145.859,7.56868,145.859);
	modeselect.cubicTo(6.26859,145.859,5.18616,145.482,4.32137,144.727);
	modeselect.cubicTo(3.45658,143.967,3.02418,142.966,3.02418,141.724);
	modeselect.cubicTo(3.02418,140.546,3.44497,139.579,4.28654,138.825);
	modeselect.cubicTo(5.12812,138.064,6.22216,137.684,7.56868,137.684);
	modeselect.cubicTo(8.95582,137.684,10.0731,138.079,10.9205,138.868);
	modeselect.cubicTo(11.762,139.652,12.1828,140.647,12.1828,141.854);
	modeselect.closeSubPath();
	modeselect.startNewSubPath(10.5461,141.785);
	modeselect.cubicTo(10.5461,140.45,9.55073,139.782,7.55997,139.782);
	modeselect.cubicTo(6.66036,139.782,5.95228,139.942,5.43573,140.261);
	modeselect.cubicTo(4.91337,140.581,4.65219,141.071,4.65219,141.733);
	modeselect.cubicTo(4.65219,142.417,4.92208,142.925,5.46184,143.256);
	modeselect.cubicTo(5.99581,143.587,6.70679,143.752,7.5948,143.752);
	modeselect.cubicTo(8.55245,143.752,9.28375,143.578,9.78869,143.23);
	modeselect.cubicTo(10.2936,142.876,10.5461,142.394,10.5461,141.785);
	modeselect.closeSubPath();
	modeselect.startNewSubPath(12.0,128.63);
	modeselect.lineTo(12.0,130.485);
	modeselect.lineTo(10.224,130.485);
	modeselect.cubicTo(11.5299,130.995,12.1828,131.86,12.1828,133.079);
	modeselect.cubicTo(12.1828,134.158,11.733,134.985,10.8334,135.56);
	modeselect.cubicTo(9.93379,136.135,8.81653,136.422,7.48162,136.422);
	modeselect.cubicTo(6.23957,136.422,5.15714,136.123,4.23431,135.525);
	modeselect.cubicTo(3.31148,134.927,2.85006,134.077,2.85006,132.974);
	modeselect.cubicTo(2.85006,131.843,3.36662,131.056,4.39972,130.615);
	modeselect.lineTo(0.116401,130.615);
	modeselect.lineTo(0.1164,128.63);
	modeselect.lineTo(12.0,128.63);
	modeselect.closeSubPath();
	modeselect.startNewSubPath(6.81126,130.615);
	modeselect.cubicTo(6.09738,130.615,5.5431,130.786,5.14843,131.129);
	modeselect.cubicTo(4.74796,131.465,4.54772,131.904,4.54772,132.443);
	modeselect.cubicTo(4.54772,133.03,4.80309,133.488,5.31384,133.819);
	modeselect.cubicTo(5.82459,134.15,6.58781,134.315,7.6035,134.315);
	modeselect.cubicTo(9.56524,134.315,10.5461,133.7,10.5461,132.469);
	modeselect.cubicTo(10.5461,131.982,10.3372,131.552,9.91928,131.181);
	modeselect.cubicTo(9.49559,130.804,8.95582,130.615,8.29998,130.615);
	modeselect.lineTo(6.81126,130.615);
	modeselect.closeSubPath();
	modeselect.startNewSubPath(9.19669,120.656);
	modeselect.lineTo(9.44045,118.862);
	modeselect.cubicTo(10.2356,119.094,10.8914,119.547,11.408,120.22);
	modeselect.cubicTo(11.9245,120.893,12.1828,121.738,12.1828,122.754);
	modeselect.cubicTo(12.1828,123.972,11.7736,124.953,10.9553,125.696);
	modeselect.cubicTo(10.1369,126.439,9.02837,126.811,7.62962,126.811);
	modeselect.cubicTo(6.30051,126.811,5.20067,126.436,4.33007,125.688);
	modeselect.cubicTo(3.45948,124.939,3.02418,123.923,3.02418,122.64);
	modeselect.cubicTo(3.02418,121.387,3.45367,120.418,4.31266,119.733);
	modeselect.cubicTo(5.17164,119.048,6.2744,118.705,7.62091,118.705);
	modeselect.lineTo(7.84727,118.714);
	modeselect.lineTo(7.84727,124.747);
	modeselect.cubicTo(8.44508,124.747,8.9239,124.692,9.28375,124.582);
	modeselect.cubicTo(9.64359,124.466,9.95701,124.239,10.224,123.903);
	modeselect.cubicTo(10.491,123.566,10.6245,123.145,10.6245,122.64);
	modeselect.cubicTo(10.6245,121.66,10.1485,120.998,9.19669,120.656);
	modeselect.closeSubPath();
	modeselect.startNewSubPath(6.5675,120.777);
	modeselect.cubicTo(5.93487,120.783,5.41831,120.975,5.01784,121.352);
	modeselect.cubicTo(4.61737,121.723,4.41713,122.185,4.41713,122.736);
	modeselect.cubicTo(4.41713,123.282,4.60576,123.737,4.98302,124.103);
	modeselect.cubicTo(5.35447,124.469,5.88263,124.683,6.5675,124.747);
	modeselect.lineTo(6.5675,120.777);
	modeselect.closeSubPath();
	modeselect.startNewSubPath(9.98022,113.508);
	modeselect.lineTo(9.62328,111.645);
	modeselect.cubicTo(10.3372,111.36,10.6941,110.734,10.6941,109.764);
	modeselect.cubicTo(10.6941,108.534,10.3314,107.919,9.60587,107.919);
	modeselect.cubicTo(9.37371,107.919,9.18218,108.015,9.03127,108.206);
	modeselect.cubicTo(8.88037,108.398,8.7788,108.624,8.72657,108.885);
	modeselect.lineTo(8.42186,110.487);
	modeselect.cubicTo(8.07943,112.263,7.21173,113.151,5.81879,113.151);
	modeselect.cubicTo(5.04106,113.151,4.38231,112.87,3.84254,112.307);
	modeselect.cubicTo(3.29697,111.744,3.02418,110.905,3.02418,109.791);
	modeselect.cubicTo(3.02418,107.933,3.70615,106.799,5.07008,106.387);
	modeselect.lineTo(5.42702,108.154);
	modeselect.cubicTo(4.76537,108.34,4.43454,108.868,4.43454,109.738);
	modeselect.cubicTo(4.43454,110.795,4.76537,111.323,5.42702,111.323);
	modeselect.cubicTo(5.88553,111.323,6.20185,110.896,6.37597,110.043);
	modeselect.lineTo(6.76773,108.154);
	modeselect.cubicTo(7.06954,106.685,7.91111,105.951,9.29245,105.951);
	modeselect.cubicTo(10.2617,105.951,10.9872,106.328,11.4689,107.083);
	modeselect.cubicTo(11.9449,107.837,12.1828,108.734,12.1828,109.773);
	modeselect.cubicTo(12.1828,110.673,12.0029,111.468,11.6431,112.159);
	modeselect.cubicTo(11.2774,112.849,10.7231,113.299,9.98022,113.508);
	modeselect.closeSubPath();
	modeselect.startNewSubPath(9.19669,98.7514);
	modeselect.lineTo(9.44045,96.958);
	modeselect.cubicTo(10.2356,97.1901,10.8914,97.6428,11.408,98.3161);
	modeselect.cubicTo(11.9245,98.9894,12.1828,99.8338,12.1828,100.85);
	modeselect.cubicTo(12.1828,102.068,11.7736,103.049,10.9553,103.792);
	modeselect.cubicTo(10.1369,104.535,9.02837,104.906,7.62962,104.906);
	modeselect.cubicTo(6.30051,104.906,5.20066,104.532,4.33007,103.783);
	modeselect.cubicTo(3.45948,103.035,3.02418,102.019,3.02418,100.736);
	modeselect.cubicTo(3.02418,99.4827,3.45367,98.5134,4.31266,97.8286);
	modeselect.cubicTo(5.17164,97.1437,6.2744,96.8013,7.62091,96.8013);
	modeselect.lineTo(7.84727,96.81);
	modeselect.lineTo(7.84727,102.843);
	modeselect.cubicTo(8.44507,102.843,8.9239,102.788,9.28375,102.678);
	modeselect.cubicTo(9.64359,102.562,9.95701,102.335,10.224,101.999);
	modeselect.cubicTo(10.491,101.662,10.6245,101.241,10.6245,100.736);
	modeselect.cubicTo(10.6245,99.7555,10.1485,99.0938,9.19669,98.7514);
	modeselect.closeSubPath();
	modeselect.startNewSubPath(6.5675,98.8733);
	modeselect.cubicTo(5.93486,98.8791,5.41831,99.0706,5.01784,99.4479);
	modeselect.cubicTo(4.61737,99.8193,4.41713,100.281,4.41713,100.832);
	modeselect.cubicTo(4.41713,101.378,4.60576,101.833,4.98302,102.199);
	modeselect.cubicTo(5.35447,102.565,5.88263,102.779,6.5675,102.843);
	modeselect.lineTo(6.5675,98.8733);
	modeselect.closeSubPath();
	modeselect.startNewSubPath(12.0,93.0142);
	modeselect.lineTo(12.0,94.9991);
	modeselect.lineTo(0.116399,94.9991);
	modeselect.lineTo(0.116399,93.0142);
	modeselect.lineTo(12.0,93.0142);
	modeselect.closeSubPath();
	modeselect.startNewSubPath(9.19669,85.0308);
	modeselect.lineTo(9.44045,83.2374);
	modeselect.cubicTo(10.2356,83.4696,10.8914,83.9223,11.408,84.5955);
	modeselect.cubicTo(11.9245,85.2688,12.1828,86.1133,12.1828,87.129);
	modeselect.cubicTo(12.1828,88.3478,11.7736,89.3287,10.9553,90.0716);
	modeselect.cubicTo(10.1369,90.8145,9.02837,91.1859,7.62962,91.1859);
	modeselect.cubicTo(6.30051,91.1859,5.20066,90.8116,4.33007,90.0629);
	modeselect.cubicTo(3.45948,89.3142,3.02418,88.2985,3.02418,87.0158);
	modeselect.cubicTo(3.02418,85.7621,3.45367,84.7929,4.31266,84.108);
	modeselect.cubicTo(5.17164,83.4231,6.27439,83.0807,7.62091,83.0807);
	modeselect.lineTo(7.84727,83.0894);
	modeselect.lineTo(7.84727,89.1226);
	modeselect.cubicTo(8.44507,89.1226,8.9239,89.0675,9.28375,88.9572);
	modeselect.cubicTo(9.64359,88.8411,9.957,88.6148,10.224,88.2782);
	modeselect.cubicTo(10.491,87.9415,10.6245,87.5207,10.6245,87.0158);
	modeselect.cubicTo(10.6245,86.0349,10.1485,85.3733,9.19669,85.0308);
	modeselect.closeSubPath();
	modeselect.startNewSubPath(6.56749,85.1527);
	modeselect.cubicTo(5.93486,85.1585,5.41831,85.3501,5.01784,85.7273);
	modeselect.cubicTo(4.61737,86.0988,4.41713,86.5602,4.41713,87.1116);
	modeselect.cubicTo(4.41713,87.6571,4.60576,88.1127,4.98302,88.4784);
	modeselect.cubicTo(5.35447,88.844,5.88263,89.0588,6.56749,89.1226);
	modeselect.lineTo(6.56749,85.1527);
	modeselect.closeSubPath();
	modeselect.startNewSubPath(8.7701,76.1943);
	modeselect.lineTo(8.94421,74.488);
	modeselect.cubicTo(10.047,74.7085,10.8624,75.1351,11.3906,75.7677);
	modeselect.cubicTo(11.9187,76.4004,12.1828,77.1636,12.1828,78.0574);
	modeselect.cubicTo(12.1828,79.2704,11.7417,80.2049,10.8595,80.8607);
	modeselect.cubicTo(9.97151,81.5108,8.88617,81.8358,7.6035,81.8358);
	modeselect.cubicTo(6.2802,81.8358,5.18615,81.4788,4.32136,80.7649);
	modeselect.cubicTo(3.45657,80.0511,3.02418,79.0992,3.02418,77.9094);
	modeselect.cubicTo(3.02418,75.9941,4.03407,74.8536,6.05384,74.488);
	modeselect.lineTo(6.2889,76.1943);
	modeselect.cubicTo(5.19776,76.3452,4.65219,76.8821,4.65219,77.8049);
	modeselect.cubicTo(4.65219,78.4782,4.94819,78.9686,5.54019,79.2762);
	modeselect.cubicTo(6.12639,79.578,6.83738,79.7289,7.67315,79.7289);
	modeselect.cubicTo(8.56115,79.7289,9.24602,79.5722,9.72775,79.2588);
	modeselect.cubicTo(10.2095,78.9396,10.4503,78.4956,10.4503,77.9268);
	modeselect.cubicTo(10.4503,77.0562,9.89026,76.4787,8.7701,76.1943);
	modeselect.closeSubPath();
	modeselect.startNewSubPath(10.4503,68.89);
	modeselect.lineTo(12.0,68.89);
	modeselect.cubicTo(12.1277,69.482,12.1915,69.9406,12.1915,70.2656);
	modeselect.cubicTo(12.1915,70.7995,12.0871,71.2581,11.8781,71.6411);
	modeselect.cubicTo(11.6634,72.0242,11.3732,72.3057,11.0075,72.4856);
	modeselect.cubicTo(10.6361,72.6597,10.0673,72.7468,9.30116,72.7468);
	modeselect.lineTo(4.74795,72.7468);
	modeselect.lineTo(4.74795,73.8437);
	modeselect.lineTo(3.207,73.8437);
	modeselect.lineTo(3.207,72.6336);
	modeselect.lineTo(0.917344,72.4508);
	modeselect.lineTo(0.769343,70.8228);
	modeselect.lineTo(3.207,70.8228);
	modeselect.lineTo(3.207,69.0555);
	modeselect.lineTo(4.74795,69.0555);
	modeselect.lineTo(4.74795,70.8228);
	modeselect.lineTo(9.03998,70.8228);
	modeselect.cubicTo(9.59135,70.8228,9.96861,70.7241,10.1718,70.5268);
	modeselect.cubicTo(10.3691,70.3236,10.4678,69.9435,10.4678,69.3863);
	modeselect.cubicTo(10.4678,69.2296,10.4619,69.0642,10.4503,68.89);
	modeselect.closeSubPath();

	g.setColour(Colour::fromRGB(172,102,117));
	g.setOpacity(1.0);
	g.fillPath(modeselect);

	// <<<<PAINT<<<< (will be overwritten!!)
	auto transform = AffineTransform::rotation(toAngle, 22, 117);
	//draggableElement = draggableElement.transformedBy(transform);

	Path Arrow1;
	Arrow1.startNewSubPath(22.0, 29.2265);
	Arrow1.lineTo(16.2265, 35.0);
	Arrow1.lineTo(22.0, 40.7735);
	Arrow1.lineTo(27.7735, 35.0);
	Arrow1.lineTo(22.0, 29.2265);
	Arrow1.closeSubPath();
	Arrow1.startNewSubPath(23.0, 110.0);
	Arrow1.lineTo(23.0, 35.0);
	Arrow1.lineTo(21.0, 35.0);
	Arrow1.lineTo(21.0, 110.0);
	Arrow1.lineTo(23.0, 110.0);
	Arrow1.closeSubPath();
	g.setColour(Colour::fromRGB(126, 77, 88));
	g.setOpacity(1.0);
	g.fillPath(Arrow1,transform);
	
	Rectangle<float> Ellipse2(14.0, 109.0, 16.0, 16.0);
	g.setColour(Colour::fromRGB(218, 132, 151));
	g.setOpacity(1.0);
	g.fillEllipse(Ellipse2);
}


// >>>>RESIZED>>>> (auto-generated)//
// <<<<RESIZED<<<< (will be overwritten!!)

// >>>>FUNCTION>>>> (auto-generated)//
// <<<<FUNCTION<<<< (will be overwritten!!)