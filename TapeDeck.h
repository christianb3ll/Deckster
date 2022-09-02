/*
  ==============================================================================

    TapeDeck.h
    Created: 2 Sep 2022 4:38:21pm
    Author:  Christian Bell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TapeDeck  : public juce::Component
{
public:
    TapeDeck();
    ~TapeDeck() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TapeDeck)
};
