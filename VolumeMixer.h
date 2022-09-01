/*
  ==============================================================================

    VolumeMixer.h
    Created: 1 Sep 2022 5:25:48pm
    Author:  Christian Bell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class VolumeMixer  : public juce::Component,
                     public Slider::Listener
{
public:
    VolumeMixer(DJAudioPlayer* player1, DJAudioPlayer* player2);
    ~VolumeMixer() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(Slider *slider) override;

private:
    Slider deck1Slider;
    Slider deck2Slider;
    
    Label deck1Label{"deck1Label", "Deck 1"};
    Label deck2Label{"deck2Label", "Deck 2"};
    
    DJAudioPlayer* player1;
    DJAudioPlayer* player2;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeMixer)
};
