/*
  ==============================================================================

	THIS CODE WAS AUTOMATICALLY GENERATED

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
using namespace juce;
// >>>>INCLUDE>>>> (auto-generated)//
// <<<<INCLUDE<<<< (will be overwritten!!)

class OnOffButton : public ToggleButton
{
public:
	OnOffButton()=delete;
	OnOffButton(AudioProcessorValueTreeState& parameters);
	~OnOffButton();

protected:
	void paintButton(Graphics&, bool isMouseOverButton, bool isButtonDown) override;

private:

	// >>>>PRIVATEMEMBERS>>>> (auto-generated)//
	void toggleOff(Graphics &);
	void toggleOffHover(Graphics &);
	void toggleOnHover(Graphics &);
	void toggleOn(Graphics &);
	// <<<<PRIVATEMEMBERS<<<< (will be overwritten!!)

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OnOffButton)
	int unusedmember;
};