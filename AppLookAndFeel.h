/*
 * AppLookAndFeel class
 *
 * Handles the look and feel of the app
 * inherits from juce::LookAndFeel_V4
 *
*/

#pragma once

#include <JuceHeader.h>

class AppLookAndFeel  :  public juce::Component,
                         public juce::LookAndFeel_V4
{
public:
    /** Constructor for AppLookAndFeel */
    AppLookAndFeel();
    
    /** Destructor for AppLookAndFeel */
    ~AppLookAndFeel() override;
    
    /** Sets up a given LookAndFeel
     * @param lookAndFeel - address of a LookAndFeel object */
    void setupLookAndFeel(LookAndFeel& lookAndFeel);
    
    /** Draws a rotary slider. Overides default Juce rotary slider
     * @param g - address of a juce::graphics object
     * @param x - int x pos of slider
     * @param y - int y pos of slider
     * @param width - int width of slider
     * @param height - int height of slider
     * @param sliderPos - float slider position
     * @param rotaryStartAngle - const float the start angle of the slideer
     * @param rotaryEndAngle - const float the end angle of the slider
     * @param slider - address of a slider */
    void drawRotarySlider(juce::Graphics& g,
                          int x,
                          int y,
                          int width,
                          int height,
                          float sliderPos,
                          const float rotaryStartAngle,
                          const float rotaryEndAngle,
                          juce::Slider& slider) override;
    
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
    
    /** Draws the background for standard buttons
     * overrides default Juse button drawing
     * @param g - address of a juce::graphics object
     * @param button - address of a button
     * @param backgroundColour - juce::Colour
     * @param isButtonHighlighted - bool button highlight status
     * @param isButtonDown - bool button down */
    void drawButtonBackground(juce::Graphics& g,
                              juce::Button& button,
                              const juce::Colour& backgroundColour,
                              bool isButtonHighlighted,
                              bool isButtonDown) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AppLookAndFeel)
};
