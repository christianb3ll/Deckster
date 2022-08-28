/*
  ==============================================================================

    Equalizer.cpp
    Created: 26 Aug 2022 5:23:52pm
    Author:  Christian Bell

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Equalizer.h"

//==============================================================================
Equalizer::Equalizer(DJAudioPlayer* _player)
                    : player(_player)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(highPassSlider);
    addAndMakeVisible(lowPassSlider);

    highPassSlider.addListener(this);
    lowPassSlider.addListener(this);

    highPassSlider.setRange(100.0, 10000.0);
    lowPassSlider.setRange(100.0, 10000.0);
    highPassSlider.setSliderStyle(Slider::LinearVertical);
    lowPassSlider.setSliderStyle(Slider::LinearVertical);
    
}

Equalizer::~Equalizer()
{
}

void Equalizer::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colour(219,219,219));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::black);
    g.setFont (14.0f);
//    g.drawText ("Equalizer", getLocalBounds(),
//                juce::Justification::centred, true);   // draw some placeholder text
    
    // Draw the EQ Dividers
    g.setColour (Colour(184,184,184));
    g.drawRect (getWidth()/3, 10, 1, getHeight()-20);
    g.drawRect ((getWidth()/3)*2, 10, 1, getHeight()-20);
    
    
}

void Equalizer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    highPassSlider.setBounds(0, 0, getWidth()/3, getHeight());
    lowPassSlider.setBounds(getWidth()/3, 0, getWidth()/3, getHeight());

}

void Equalizer::sliderValueChanged(Slider *slider){
    if(slider == &highPassSlider){
        this->highPassFreq = slider->getValue();
        player->setFilterCoefficients(IIRCoefficients::makeHighPass(44000, this->highPassFreq));
    }
    
    if(slider == &lowPassSlider){
        this->lowPassFreq = slider->getValue();
        player->setFilterCoefficients(IIRCoefficients::makeLowPass(44000, this->lowPassFreq));
    }
    
}

double Equalizer::getHighPassFrequency(){
    return this->highPassFreq;
}
