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
    addAndMakeVisible(highPassToggle);
    
    addAndMakeVisible(lowPassSlider);
    addAndMakeVisible(lowPassToggle);
    
    
    // HighPass Slider
    highPassSlider.addListener(this);
    highPassToggle.addListener(this);
    highPassSlider.setRange(1000, 20000.0);
    highPassSlider.setValue(1000);
    highPassSlider.setSliderStyle(Slider::LinearVertical);
    highPassSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, highPassSlider.getTextBoxWidth(), highPassSlider.getTextBoxHeight());
    highPassSlider.setNumDecimalPlacesToDisplay(0);
    highPassSlider.setEnabled(highPass);
    
    
    
    // LowPass Slider
    lowPassSlider.addListener(this);
    lowPassToggle.addListener(this);
    lowPassSlider.setRange(2.0, 500.0);
    lowPassSlider.setValue(500.0);
    lowPassSlider.setSliderStyle(Slider::LinearVertical);
    lowPassSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, lowPassSlider.getTextBoxWidth(), lowPassSlider.getTextBoxHeight());
    lowPassSlider.setNumDecimalPlacesToDisplay(0);
    lowPassSlider.setEnabled(lowPass);
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

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::black);
    g.setFont (14.0f);
    
    // Draw the EQ Dividers
    g.setColour (Colour(184,184,184));
    g.drawRect (getWidth()/2, 10, 1, getHeight()-20);
    
    
    
}

void Equalizer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    highPassToggle.setBounds(0, 0, getWidth()/4, getHeight());
    highPassSlider.setBounds(getWidth()/4, 0, getWidth()/4, getHeight());
    
    lowPassToggle.setBounds(getWidth()/2, 0, getWidth()/4, getHeight());
    lowPassSlider.setBounds((getWidth()/4)*3, 0, getWidth()/4, getHeight());

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

void Equalizer::buttonClicked(Button *button){
    if(button == &highPassToggle){
        this->highPass = !highPass;
        highPassSlider.setEnabled(highPass);
        if(!highPass) player->deactivateFilter();
    }
    
    if(button == &lowPassToggle){
        this->lowPass = !lowPass;
        lowPassSlider.setEnabled(lowPass);
    }
}

double Equalizer::getHighPassFrequency(){
    return this->highPassFreq;
}

double Equalizer::getLowPassFrequency(){
    return this->lowPassFreq;
}
