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
    
    
    // HighPass Slider
    highPassSlider.addListener(this);
    highPassSlider.setRange(100.0, 10000.0);
    highPassSlider.setSliderStyle(Slider::LinearVertical);
    highPassSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, highPassSlider.getTextBoxWidth(), highPassSlider.getTextBoxHeight());
    highPassSlider.setNumDecimalPlacesToDisplay(0);
    
    // LowPass Slider
    lowPassSlider.addListener(this);
    lowPassSlider.setRange(100.0, 10000.0);
    lowPassSlider.setSliderStyle(Slider::LinearVertical);
    lowPassSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, lowPassSlider.getTextBoxWidth(), lowPassSlider.getTextBoxHeight());
    lowPassSlider.setNumDecimalPlacesToDisplay(0);
    
//    highPassLabel.setFont(18.0);
//    highPassLabel.setText("High Pass", NotificationType::dontSendNotification);
//    highPassLabel.setColour(Label::ColourIds::textColourId, juce::Colours::black);
//    highPassLabel.setJustificationType(Justification::centredBottom);
//    highPassLabel.attachToComponent(&highPassSlider, false);
//    
//    
//    lowPassLabel.setFont(18.0);
//    lowPassLabel.setText("Low Pass", NotificationType::dontSendNotification);
//    lowPassLabel.setColour(Label::ColourIds::textColourId, juce::Colours::black);
//    lowPassLabel.setJustificationType(Justification::centredBottom);
//    lowPassLabel.attachToComponent(&lowPassSlider, false);
    
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
//    g.drawText ("Equalizer", getLocalBounds(),
//                juce::Justification::centred, true);   // draw some placeholder text
    
    // Draw the EQ Dividers
    g.setColour (Colour(184,184,184));
    g.drawRect (getWidth()/3, 10, 1, getHeight()-20);
    g.drawRect ((getWidth()/3)*2, 10, 1, getHeight()-20);
    
    // Draw the labels
    
    
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
