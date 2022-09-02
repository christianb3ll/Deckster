#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 900);
    
    // Setup the Look and Feel
    setLookAndFeel(&appLookAndFeel);
    this->appLookAndFeel.setupLookAndFeel(appLookAndFeel);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
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
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
    setLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    
    
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
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
//    transportSource.releaseResources();
    mixerSource.removeAllInputs();
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions
    
    double deckHeight = getHeight() - getHeight()/3;
    deckGUI1.setBounds(5, 5, (getWidth()/2)-10, deckHeight-10);
    deckGUI2.setBounds(getWidth()/2 +5, 5, (getWidth()/2)-10, deckHeight-10);
    
    double mixerHeight = 50;
    volumeMixer.setBounds(5,deckHeight, getWidth()-10,mixerHeight);
    playlistComponent.setBounds(5, deckHeight + mixerHeight+5, getWidth()-10, (getHeight()/3)-mixerHeight-10);
}
