#include <JuceHeader.h>
#include "Equalizer.h"

/** Constructor for Equalizer class */
Equalizer::Equalizer(DJAudioPlayer* _player)
                    : player(_player)
{
    addAndMakeVisible(highPassSlider);
    addAndMakeVisible(highPassToggle);
    
    addAndMakeVisible(lowPassSlider);
    addAndMakeVisible(lowPassToggle);
    
    
    // HighPass Slider
    highPassSlider.addListener(this);
    highPassToggle.addListener(this);
    highPassSlider.setRange(10, 20000.0);
    highPassSlider.setValue(10);
    highPassSlider.setSliderStyle(Slider::LinearVertical);
    highPassSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, highPassSlider.getTextBoxWidth(), highPassSlider.getTextBoxHeight());
    highPassSlider.setNumDecimalPlacesToDisplay(0);
    highPassSlider.setEnabled(highPass);
    
    // LowPass Slider
    lowPassSlider.addListener(this);
    lowPassToggle.addListener(this);
    lowPassSlider.setRange(2.0, 2000.0);
    lowPassSlider.setValue(2000.0);
    lowPassSlider.setSliderStyle(Slider::LinearVertical);
    lowPassSlider.setTextBoxStyle(juce::Slider::TextBoxRight, true, lowPassSlider.getTextBoxWidth(), lowPassSlider.getTextBoxHeight());
    lowPassSlider.setNumDecimalPlacesToDisplay(0);
    lowPassSlider.setEnabled(lowPass);
}

/** Destructor for Equalizer class */
Equalizer::~Equalizer()
{
}

/** gets called when a region of a component needs redrawing */
void Equalizer::paint (juce::Graphics& g)
{
    // Draw the background
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    // Draw the outline
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
    
    // Draw the EQ Divider
    g.setColour (Colour(184,184,184));
    g.drawRect (getWidth()/2, 10, 1, getHeight()-20);
}

/** Called when this component's size has been changed. */
void Equalizer::resized()
{
    highPassToggle.setBounds(0, 0, getWidth()/4, getHeight());
    highPassSlider.setBounds(getWidth()/4, 0, getWidth()/4, getHeight());
    
    lowPassToggle.setBounds(getWidth()/2, 0, getWidth()/4, getHeight());
    lowPassSlider.setBounds((getWidth()/4)*3, 0, getWidth()/4, getHeight());
}

/** Detects changes to sliders and updates values */
void Equalizer::sliderValueChanged(Slider *slider){
    // High Pass Slider
    if(slider == &highPassSlider){
        this->enableHighPass();
    }
    
    // Low Pass Slider
    if(slider == &lowPassSlider){
        this->enableLowPass();
    }
}

/** Detects a button click and takes appropriate action depending on button clicked */
void Equalizer::buttonClicked(Button *button){
    // High Pass Toggle
    if(button == &highPassToggle){
        this->highPass = !highPass;
        highPassSlider.setEnabled(highPass);
        if(!highPass) player->deactivateFilter("highPass");
        if(highPass) this->enableHighPass();
    }
    
    // Low Pass Toggle
    if(button == &lowPassToggle){
        this->lowPass = !lowPass;
        lowPassSlider.setEnabled(lowPass);
        if(!lowPass) player->deactivateFilter("lowPass");
        if(lowPass) this->enableLowPass();
    }
}

/** returns the highPassFrequency */
double Equalizer::getHighPassFrequency(){
    return this->highPassFreq;
}

/** returns the lowPassFrequency */
double Equalizer::getLowPassFrequency(){
    return this->lowPassFreq;
}

/** enables HighPass */
void Equalizer::enableHighPass(){
    this->highPassFreq = this->highPassSlider.getValue();
    if(!player->getCurrentTrack().empty()){
        player->setHighPassCoefficients(IIRCoefficients::makeHighPass(player->getCurrentSampleRate(), this->highPassFreq));
    }
}

/** enables LowPass */
void Equalizer::enableLowPass(){
    this->lowPassFreq = this->lowPassSlider.getValue();
    if(!player->getCurrentTrack().empty()){
        player->setLowPassCoefficients(IIRCoefficients::makeLowPass(player->getCurrentSampleRate(), this->lowPassFreq));
    }
}
