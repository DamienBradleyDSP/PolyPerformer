/*
  ==============================================================================

	THIS CODE WAS AUTOMATICALLY GENERATED

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
using namespace juce;
// >>>>INCLUDE>>>> (auto-generated)//
#include "sustainSlider.h"
#include "noteSelector.h"
#include "OnOffButton.h"
#include "rhythmLoader.h"
// <<<<INCLUDE<<<< (will be overwritten!!)

//==============================================================================
/*
*/
class polyModule : public Component, Button::Listener
{
public:
	polyModule() =delete;
	polyModule(AudioProcessorValueTreeState& parameters, juce::Button::Listener& p, int moduleNumber);
    ~polyModule();

    void paint (Graphics&) override;
    void resized() override;

	void setModuleName(juce::String presetName);

	void updateStateInformation();

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(polyModule)
	int unusedmember;

	void buttonClicked(Button*) override;

	const int moduleNumber;

	// >>>>PRIVATEMEMBERS>>>> (auto-generated)//
	juce::Slider sustainSliderSlider1;
	noteSelector noteSelector1;
	OnOffButton OnOffButton1;
	rhythmLoader rhythmLoader1;
	// <<<<PRIVATEMEMBERS<<<< (will be overwritten!!)

	MidiKeyboardState noteSelectorKeyState;
	MidiKeyboardComponent noteSelectorKeyboard;

	RangedAudioParameter* moduleOnOff;
	RangedAudioParameter* moduleNoteNumber;
	RangedAudioParameter* moduleRelease;
};
