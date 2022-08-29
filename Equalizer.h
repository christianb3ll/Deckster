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
                   public Button::Listener,
                   public Slider::Listener
{
public:
    Equalizer(DJAudioPlayer* player);
    ~Equalizer() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider *slider) override;
    
    void buttonClicked(Button *button) override;
    
    double getHighPassFrequency();
    
    double getLowPassFrequency();

private:
    DJAudioPlayer* player;
    
    Slider highPassSlider;
    ToggleButton highPassToggle{"High Pass"};
    double highPassFreq;
    bool highPass = false;
    
    Slider lowPassSlider;
    ToggleButton lowPassToggle{"Low Pass"};
    double lowPassFreq;
    bool lowPass = false;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Equalizer)
};
