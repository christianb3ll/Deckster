/*
 * TapeDeck class
 *
 * Handles the display of the tape deck and speaker sections
 * draws the graphics and has methods to update the position and speed
 * for tape response
 *
*/

#pragma once

#include <JuceHeader.h>

class TapeDeck  : public juce::Component
{
public:
    /** Constructor for TapeDeck class */
    TapeDeck();
    
    /** Destructor for TapeDeck class */
    ~TapeDeck() override;

    /** gets called when a region of a component needs redrawing
     * @param the graphics context that must be used for the drawing operation. */
    void paint (juce::Graphics&) override;
    
    /** Called when this component's size has been changed. */
    void resized() override;
    
    /** Set the relative position for tape rotation
     * @param pos relative position as a double */
    void setPositionRelative(double pos);
    
    /** sets the speed as a ratio between 1 and 100
     * @param ratio - ratio as double */
    void setSpeed(double ratio);

private:
    double position;
    double speed;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TapeDeck)
};
