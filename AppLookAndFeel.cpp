#include <JuceHeader.h>
#include "AppLookAndFeel.h"

/** Constructor for AppLookAndFeel */
AppLookAndFeel::AppLookAndFeel()
{
}

/** Destructor for AppLookAndFeel */
AppLookAndFeel::~AppLookAndFeel()
{
}

/** Sets up a given LookAndFeel */
void AppLookAndFeel::setupLookAndFeel(LookAndFeel& lookAndFeel){
    // Main Window
    lookAndFeel.setColour (juce::ResizableWindow::backgroundColourId, Colour(217,217,217));
    
    // Buttons
    lookAndFeel.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    
    // Toggle Button
    lookAndFeel.setColour(juce::ToggleButton::textColourId, juce::Colours::black);
    lookAndFeel.setColour(juce::ToggleButton::tickColourId, juce::Colours::black);
    lookAndFeel.setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::black);
    
    // Default Slider
    lookAndFeel.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    lookAndFeel.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    lookAndFeel.setColour(juce::Slider::thumbColourId, juce::Colours::white);
    
    // Labels
    lookAndFeel.setColour(juce::Label::textColourId, juce::Colours::black);
    
    // Table
    lookAndFeel.setColour(juce::TableHeaderComponent::backgroundColourId, juce::Colours::white);
    lookAndFeel.setColour(juce::TableHeaderComponent::textColourId, juce::Colours::black);
    
    lookAndFeel.setColour(juce::ListBox::backgroundColourId, juce::Colours::darkgrey);
    lookAndFeel.setColour(juce::ListBox::textColourId, juce::Colours::black);
}

/** Draws a rotary slider. Overides default Juce rotary slider */
void AppLookAndFeel::drawRotarySlider(juce::Graphics& g,
                      int x,
                      int y,
                      int width,
                      int height,
                      float sliderPos,
                      const float rotaryStartAngle,
                      const float rotaryEndAngle,
                      juce::Slider& slider){
    // https://docs.juce.com/master/tutorial_look_and_feel_customisation.html
    auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
    auto centreX = (float) x + (float) width  * 0.5f;
    auto centreY = (float) y + (float) height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    // fill
    g.setColour(Colour(200,200,200));
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour(Colour(150,150,150));
    g.drawEllipse (rx, ry, rw, rw, 1.0f);
    
    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 2.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform(juce::AffineTransform::rotation (angle).translated (centreX, centreY));
    
    // pointer
    g.setColour(Colour(100,100,100));
    g.fillPath(p);
}


//void AppLookAndFeel::drawLinearSlider(Graphics& g,
//                                int x,
//                                int y,
//                                int width,
//                                int height,
//                                float sliderPos,
//                                float minSliderPos,
//                                float maxSliderPos,
//                                const Slider::SliderStyle style,
//                                Slider &){
//    g.setColour(Colour(255,0,0));
////    Rectangle<int> test = Rectangle(maxSliderPos, y, 5, height);
////    g.drawRect(test);
//    g.drawEllipse(maxSliderPos, y, 20, height, 8);
//}

/** Draws the background for standard buttons
 * overrides default Juse button drawing */
void AppLookAndFeel::drawButtonBackground(juce::Graphics& g,
                          juce::Button& button,
                          const juce::Colour& backgroundColour,
                          bool isHighlighted,
                          bool isButtonDown){
    auto buttonArea = button.getLocalBounds();
    g.setColour(backgroundColour);
    g.drawRect(buttonArea);
    
    if(isHighlighted){
        g.setColour(juce::Colours::lightslategrey);
        g.fillRect(buttonArea);
    }
    if(isButtonDown){
        g.setColour(juce::Colours::darkgrey);
        g.fillRect(buttonArea);
    }
}


