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
class noteSelector : public Button
{
public:
	noteSelector()=delete;
	noteSelector(AudioProcessorValueTreeState& parameters);
    ~noteSelector();

protected:
	void paintButton(Graphics&, bool isMouseOverButton, bool isButtonDown) override;

private:

	// >>>>PRIVATEMEMBERS>>>> (auto-generated)//
	Label noteDisplay1;
	// <<<<PRIVATEMEMBERS<<<< (will be overwritten!!)

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (noteSelector)
};
