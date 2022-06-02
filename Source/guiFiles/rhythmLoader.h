/*
  ==============================================================================

	THIS CODE WAS AUTOMATICALLY GENERATED

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
using namespace juce;
// >>>>INCLUDE>>>> (auto-generated)//
// <<<<INCLUDE<<<< (will be overwritten!!)

//==============================================================================
/*
*/
class rhythmLoader : public Button
{
public:
	rhythmLoader() =delete;
	rhythmLoader(AudioProcessorValueTreeState& parameters, juce::Button::Listener& p);
    ~rhythmLoader();

	void paintButton(Graphics&, bool isMouseOverButton, bool isButtonDown) override;

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(rhythmLoader)
	int unusedmember;

	// >>>>PRIVATEMEMBERS>>>> (auto-generated)//
	Label fileName1;
	// <<<<PRIVATEMEMBERS<<<< (will be overwritten!!)
};
