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

    highPassSlider.addListener(this);

    highPassSlider.setRange(100.0, 10000.0);
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

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Equalizer", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void Equalizer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    highPassSlider.setBounds(0, 0, getWidth(), getHeight()/2);

}

void Equalizer::sliderValueChanged(Slider *slider){
    if(slider == &highPassSlider){
        this->highPassFreq = slider->getValue();
        
        player->setFilterCoefficients(IIRCoefficients::makeHighPass(44000, this->highPassFreq));
    }
    
}

double Equalizer::getHighPassFrequency(){
    return this->highPassFreq;
}
