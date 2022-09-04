#include <JuceHeader.h>
#include "VolumeMixer.h"

/** Constructor for VolumeMixer class */
VolumeMixer::VolumeMixer(DJAudioPlayer* _player1, DJAudioPlayer* _player2)
                        : player1(_player1),
                          player2(_player2)
{
    addAndMakeVisible(deck1Slider);
    addAndMakeVisible(deck2Slider);
    addAndMakeVisible(deck1Label);
    addAndMakeVisible(deck2Label);
    
    deck1Label.attachToComponent(&deck1Slider,true);
    deck2Label.attachToComponent(&deck2Slider,true);
    
    deck1Slider.addListener(this);
    deck2Slider.addListener(this);
    
    deck1Slider.setRange(0.0, 1.0);
    deck2Slider.setRange(0.0, 1.0);
    
    deck1Slider.setValue(1.0);
    deck2Slider.setValue(1.0);
    
    deck1Slider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    deck2Slider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
}

/** Destructor for VolumeMixer class */
VolumeMixer::~VolumeMixer()
{
}

/** gets called when a region of a component needs redrawing */
void VolumeMixer::paint (juce::Graphics& g)
{
    // Draw the background
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    // Draw the border
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1); 
}

/** Called when this component's size has been changed. */
void VolumeMixer::resized()
{
    double sliderWidth = getWidth()/4;
    deck1Slider.setBounds(getWidth()/2 - sliderWidth, 0, sliderWidth, getHeight());
    deck2Slider.setBounds(getWidth() - sliderWidth, 0, sliderWidth, getHeight());
}

/** Detects changes to sliders and updates values */
void VolumeMixer::sliderValueChanged(Slider *slider){
    // Deck 1 slider
    if(slider == &deck1Slider){
        player1->setGain(slider->getValue());
    }
    
    // Deck 2 slider
    if(slider == &deck2Slider){
        player2->setGain(slider->getValue());
    }
}
