/*
  ==============================================================================

	THIS CODE WAS AUTOMATICALLY GENERATED

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
using namespace juce;
// >>>>INCLUDE>>>> (auto-generated)//
#include "modeSelector.h"
// <<<<INCLUDE<<<< (will be overwritten!!)
#include "polyModule.h"

//==============================================================================
/*
*/
class guiBounds : public Component
{
public:
	guiBounds() =delete;
	guiBounds(AudioProcessorValueTreeState& parameters);
    ~guiBounds();

    void paint (Graphics&) override;
    void resized() override;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(guiBounds)
	int unusedmember;

	// >>>>PRIVATEMEMBERS>>>> (auto-generated)//
	juce::Slider modeSelectorSlider1;
	Rectangle<int> polyModuleArea;
	// <<<<PRIVATEMEMBERS<<<< (will be overwritten!!)

	const int polyModulepixelGap = 7;
	
	std::vector<std::unique_ptr<polyModule>> polyModules;
};
