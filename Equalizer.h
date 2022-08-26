/*
  ==============================================================================

    Equalizer.h
    Created: 26 Aug 2022 5:23:52pm
    Author:  Christian Bell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Equalizer  : public juce::Component
{
public:
    Equalizer();
    ~Equalizer() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Equalizer)
};
