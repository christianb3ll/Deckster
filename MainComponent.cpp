#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (800, 900);
    
    // Setup the Look and Feel
    setLookAndFeel(&appLookAndFeel);
    this->appLookAndFeel.setupLookAndFeel(appLookAndFeel);

    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        setAudioChannels (2, 2);
    }
    
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    
    addAndMakeVisible(volumeMixer);
    
    addAndMakeVisible(playlistComponent);
    
    formatManager.registerBasicFormats();

}

MainComponent::~MainComponent()
{
    shutdownAudio();
    setLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
    
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    mixerSource.removeAllInputs();
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{    
    double deckHeight = getHeight() - getHeight()/3;
    deckGUI1.setBounds(5, 5, (getWidth()/2)-10, deckHeight-10);
    deckGUI2.setBounds(getWidth()/2 +5, 5, (getWidth()/2)-10, deckHeight-10);
    
    double mixerHeight = 50;
    volumeMixer.setBounds(5,deckHeight, getWidth()-10,mixerHeight);
    playlistComponent.setBounds(5, deckHeight + mixerHeight+5, getWidth()-10, (getHeight()/3)-mixerHeight-10);
}
