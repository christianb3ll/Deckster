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
    
    
    bool isInterestedInFileDrag (const StringArray &files) override;
    
    void filesDropped (const StringArray &files, int x, int y) override;

    void timerCallback() override;
    
    void loadTrack(URL track);
    
    
    void mouseDown(const MouseEvent &event) override;
    
private:
    TextButton playButton{"PLAY"};
    TextButton stopButton{"STOP"};
    TextButton loadButton{"LOAD"};
    
    Slider volSlider;
    Slider speedSlider;
//    Slider posSlider;
    
    Equalizer equalizer;
    
    DJAudioPlayer* player;
    
    WaveformDisplay waveformDisplay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
