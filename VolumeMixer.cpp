/*
  ==============================================================================

    VolumeMixer.cpp
    Created: 1 Sep 2022 5:25:48pm
    Author:  Christian Bell

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VolumeMixer.h"

//==============================================================================
VolumeMixer::VolumeMixer(DJAudioPlayer* _player1, DJAudioPlayer* _player2)
                        : player1(_player1),
                          player2(_player2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
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

VolumeMixer::~VolumeMixer()
{
}

void VolumeMixer::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

 
}

void VolumeMixer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    double sliderWidth = getWidth()/4;
    double labelWidth = 50;
    deck1Slider.setBounds(labelWidth, 0, sliderWidth, getHeight());
    deck2Slider.setBounds(getWidth() - sliderWidth, 0, sliderWidth, getHeight());

}

void VolumeMixer::sliderValueChanged(Slider *slider){
    if(slider == &deck1Slider){
        player1->setGain(slider->getValue());
    }
    
    if(slider == &deck2Slider){
        player2->setGain(slider->getValue());
    }
}
