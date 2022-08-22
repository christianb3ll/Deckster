/*
 * WaveformDisplay class
 *
 * handles the display and painting of the waveform display area
 * and sets the current playhead position
 *
*/

#pragma once

#include <JuceHeader.h>

class WaveformDisplay  : public juce::Component,
                         public ChangeListener
{
public:
    /** Constructor for WaveformDisplay class
     * @param formatManagerToUse reference to a AudioFormatManager
     * @param cacheToUse referemnce to a AudioThumbnailCache */
    WaveformDisplay(AudioFormatManager & formatManagerToUse,
                    AudioThumbnailCache & cacheToUse);
    
    /** Destructor for WaveformDisplay class */
    ~WaveformDisplay() override;

    /** gets called when a region of a component needs redrawing
     * @param the graphics context that must be used for the drawing operation. */
    void paint (juce::Graphics&) override;
    
    /** Called when this component's size has been changed. */
    void resized() override;
    
    /** Receives change event callbacks that are sent out by a ChangeBroadcaster.
     * @param source pointer to a ChangeBroadcaster source */
    void changeListenerCallback(ChangeBroadcaster *source) override;
    
    /** loads a given URL and clears any existing thumbnail
     * @param audioURL a audio file URL */
    void loadURL(URL audioURL);
    
    /** Set the relative position of the playhead
     * @param pos relative position as a double */
    void setPositionRelative(double pos);

private:
    AudioThumbnail audioThumb;
    bool fileLoaded;
    double position;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
