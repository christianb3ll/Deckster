/*
 * VolumeMixer class
 *
 * Handles the volume sliders for each deck
 * Moved from DeckGUI class
 *
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class VolumeMixer  : public juce::Component,
                     public Slider::Listener
{
public:
    /** Constructor for VolumeMixer class
     * @param player1 - address of a DJAudioPlayer
     * @param player2 - address of a DJAudioPlayer */
    VolumeMixer(DJAudioPlayer* player1, DJAudioPlayer* player2);
    
    /** Destructor for VolumeMixer class */
    ~VolumeMixer() override;

    /** gets called when a region of a component needs redrawing
     * @param the graphics context that must be used for the drawing operation. */
    void paint (juce::Graphics&) override;
    
    /** Called when this component's size has been changed. */
    void resized() override;
    
    /** Detects changes to sliders and updates values
     * @param slider address of a slider */
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
