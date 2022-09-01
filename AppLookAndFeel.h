/*
  ==============================================================================

    AppLookAndFeel.h
    Created: 1 Sep 2022 9:36:11pm
    Author:  Christian Bell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AppLookAndFeel  :  public juce::Component,
                         public juce::LookAndFeel_V4
{
public:
    AppLookAndFeel();
    ~AppLookAndFeel() override;
    
    void drawRotarySlider(juce::Graphics& g,
                          int x,
                          int y,
                          int width,
                          int height,
                          float sliderPos,
                          const float rotaryStartAngle,
                          const float rotaryEndAngle,
                          juce::Slider&) override;
    
//    void drawLinearSlider(Graphics &,
//                                    int x,
//                                    int y,
//                                    int width,
//                                    int height,
//                                    float sliderPos,
//                                    float minSliderPos,
//                                    float maxSliderPos,
//                                    const Slider::SliderStyle style,
//                                    Slider &) override;
    
    
    void drawButtonBackground(juce::Graphics& g,
                              juce::Button& button,
                              const juce::Colour& backgroundColour,
                              bool,
                              bool isButtonDown) override;
    

    


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AppLookAndFeel)
};
