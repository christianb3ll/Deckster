/*
 * Eqiualizer class
 *
 * Handles the drawing and GUI of the Equalizer
 * Sneds values to the DJAudioPlayer
 *
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class Equalizer  : public juce::Component,
                   public Button::Listener,
                   public Slider::Listener
{
public:
    /** Constructor for Equalizer class
     * @param player - address of a DJAudioPlayer object */
    Equalizer(DJAudioPlayer* player);
    
    /** Destructor for Equalizer class */
    ~Equalizer() override;

    /** gets called when a region of a component needs redrawing
     * @param the graphics context that must be used for the drawing operation. */
    void paint (juce::Graphics&) override;
    
    /** Called when this component's size has been changed. */
    void resized() override;
    
    /** Detects changes to sliders and updates values
     * @param slider address of a slider */
    void sliderValueChanged(Slider *slider) override;
    
    /** Detects a button click and takes appropriate action depending on button clicked
     * @param Button pointer */
    void buttonClicked(Button *button) override;
    
    /** returns the highPassFrequency
     * @return highPassFrequency as double */
    double getHighPassFrequency();
    
    /** returns the lowPassFrequency
     * @return lowPassFrequency as double */
    double getLowPassFrequency();
    
    /** enables HighPass */
    void enableHighPass();
    
    /** enables LowPass */
    void enableLowPass();

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
