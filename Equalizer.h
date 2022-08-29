/*
  ==============================================================================

    Equalizer.h
    Created: 26 Aug 2022 5:23:52pm
    Author:  Christian Bell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class Equalizer  : public juce::Component,
                   public Slider::Listener
{
public:
    Equalizer(DJAudioPlayer* player);
    ~Equalizer() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider *slider) override;
    
    double getHighPassFrequency();

private:
    DJAudioPlayer* player;
    Slider highPassSlider;
//    Label highPassLabel;
    double highPassFreq;
    
    Slider lowPassSlider;
//    Label lowPassLabel;
    double lowPassFreq;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Equalizer)
};
