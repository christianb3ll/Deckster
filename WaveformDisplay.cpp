#include <JuceHeader.h>
#include "WaveformDisplay.h"

/** Constructor for WaveformDisplay class */
WaveformDisplay::WaveformDisplay(AudioFormatManager & formatManagerToUse,
                                 AudioThumbnailCache & cacheToUse) : audioThumb(1000, formatManagerToUse, cacheToUse),
                                        fileLoaded(false),
                                        position(0)
{
    audioThumb.addChangeListener(this);
}

/** Destructor for WaveformDisplay class */
WaveformDisplay::~WaveformDisplay()
{
}

/** gets called when a region of a component needs redrawing */
void WaveformDisplay::paint (juce::Graphics& g)
{
    // Draw background
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId)); 
    // draw border
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);

    // Draw waveform window
    g.setColour (Colour(57,57,57));
    auto waveformWindow = getLocalBounds().toFloat().reduced (10.0);
    g.fillRoundedRectangle (waveformWindow, 8.0);
    
    // Draw the waveform and playhead
    g.setColour (juce::Colours::limegreen);
    if(fileLoaded){
        audioThumb.drawChannel(g, getLocalBounds().reduced(10), 0, audioThumb.getTotalLength(), 0, 1.0f);
        g.setColour(Colour(255,122,0));
        g.drawRect(10 + (position * getWidth()), 10, 2, getHeight()-20);
        
    } else {
        g.setFont (20.0f);
        g.drawText ("File not loaded...", getLocalBounds(),
                    juce::Justification::centred, true);
    }
}

/** Called when this component's size has been changed. */
void WaveformDisplay::resized()
{
}

/** Receives change event callbacks that are sent out by a ChangeBroadcaster. */
void WaveformDisplay::changeListenerCallback(ChangeBroadcaster *source){
    repaint();
}

/** loads a given URL and clears any existing thumbnail */
void WaveformDisplay::loadURL(URL audioURL){
    // Clear any existing thumbs
    audioThumb.clear();
    
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
    
    if(fileLoaded){
        std::cout << "File loaded" << std::endl;
    } else {
        std::cout << "File not loaded" << std::endl;
    }
}

/** Set the relative position of the playhead */
void WaveformDisplay::setPositionRelative(double pos){
    if(pos != position){
        position = pos;
        repaint();
    }
}
