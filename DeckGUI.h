/*
 * DeckGUI class
 *
 * handles the display and control of all GUI elements
 * for each deck
 *
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "Equalizer.h"
#include "AppLookAndFeel.h"
#include "TapeDeck.h"

class DeckGUI  : public juce::Component,
                 public Button::Listener,
                 public Slider::Listener,
                 public FileDragAndDropTarget,
                 public Timer
{
public:
    /** Constructor for DJAudioPlayer class
     * @param player pointer to a DJAudioPlayer
     * @param formatManagerToUSe a  AudioFormatManager reference
     * @param cacheToUse a AudioThumbnailCache reference */
    DeckGUI(DJAudioPlayer* player,
            AudioFormatManager & formatManagerToUse,
            AudioThumbnailCache & cacheToUse);

    /** Constructor for DJAudioPlayer class */
    ~DeckGUI() override;

    /** gets called when a region of a component needs redrawing
     * @param the graphics context that must be used for the drawing operation. */
    void paint (juce::Graphics&) override;
    
    /** Called when this component's size has been changed. */
    void resized() override;
    
    /** Detects a button click and takes appropriate action depending on button clicked
     * @param Button pointer */
    void buttonClicked(Button *) override;
    
    /** Detects changes to sliders and updates values
     * @param slider pointer to a slider */
    void sliderValueChanged(Slider *slider) override;
    
    /** called when slider drag has ended
     * @param slider pointer to a slider */
    void sliderDragEnded(Slider *slider) override;

    
    /** Callback to check whether this target is interested in the set of files being offered.
     * @param &files - address of a string array of files
     * @return bool */
    bool isInterestedInFileDrag(const StringArray &files) override;
    
    /** Callback to indicate that the user has dropped the files onto this component.
     * @param &files - string array of files
     * @param x - int x drop location
     * @param y - int y drop location */
    void filesDropped(const StringArray &files, int x, int y) override;

    /** user-defined callback routine that gets called periodically */
    void timerCallback() override;
    
    /** Loads a track into the deck
     * @param track - track URL */
    void loadTrack(URL track);
    
    /** detects mouse clicks
     * @param &event - address of a mouse event */
    void mouseDown(const MouseEvent &event) override;
    
    /** detects mouse release
     * @param &event - address of a mouse event */
    void mouseUp(const MouseEvent &event) override;
    
private:
    // Image Buttons
    ImageButton playButton;
    ImageButton stopButton;
    ImageButton loadButton;
    ImageButton fastforwardButton;
    ImageButton loopButton;
    
    // Sliders
    Slider volSlider;
    Slider speedSlider;
    
    DJAudioPlayer* player;
    Equalizer equalizer{player};
    TapeDeck tapeDeck;
    WaveformDisplay waveformDisplay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
