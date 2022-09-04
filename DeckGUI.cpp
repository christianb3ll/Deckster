#include <JuceHeader.h>
#include "DeckGUI.h"
#include "Equalizer.h"

/** Constructor for DJAudioPlayer class */
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 AudioFormatManager & formatManagerToUse,
                 AudioThumbnailCache & cacheToUse
                 ) : player(_player),
                     waveformDisplay(formatManagerToUse, cacheToUse)
{
    // Buttons
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(fastforwardButton);
    addAndMakeVisible(loopButton);
    
    // Sliders
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    
    // Child components
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(tapeDeck);
    addAndMakeVisible(equalizer);
    
    // Button Listeners
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    fastforwardButton.addListener(this);
    loopButton.addListener(this);
    
    // Slider Listeners
    volSlider.addListener(this);
    speedSlider.addListener(this);
    
    // Mouse Listener
    waveformDisplay.addMouseListener(this, false);
    fastforwardButton.addMouseListener(this, false);

    // Setup Sliders
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(1,20.0);
    speedSlider.setSliderStyle(Slider::Rotary);
    speedSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    
    // Setup Timer
    startTimer(500);
    
    // Setup the Image Buttons
    // Set up Play Button images
    Image playIcon = ImageCache::getFromMemory(BinaryData::playbutton_png, BinaryData::playbutton_pngSize);
    playButton.setImages (false, false, true, playIcon, 1.0f, {}, playIcon, 0.8f, {}, playIcon, 1.0f, {juce::Colours::transparentWhite});
    
    // Set up Stop Button images
    Image pauseIcon = ImageCache::getFromMemory(BinaryData::pausebutton_png, BinaryData::pausebutton_pngSize);
    stopButton.setImages (false, false, true, pauseIcon, 1.0f, {}, pauseIcon, 0.8f, {}, pauseIcon, 1.0f, {juce::Colours::transparentWhite});
    
    // Set up Fast Forward Button images
    Image fastforwardIcon = ImageCache::getFromMemory(BinaryData::fastforwardbutton_png, BinaryData::fastforwardbutton_pngSize);
    fastforwardButton.setImages (false, false, true, fastforwardIcon, 1.0f, {}, fastforwardIcon, 0.8f, {}, fastforwardIcon, 1.0f, {juce::Colours::transparentWhite});
    
    // Set up Loop Button images
    Image loopIcon = ImageCache::getFromMemory(BinaryData::loopbutton_png, BinaryData::loopbutton_pngSize);
    loopButton.setImages (false, false, true, loopIcon, 1.0f, {}, loopIcon, 0.8f, {}, loopIcon, 1.0f, {juce::Colours::transparentWhite});
    
    // Set up Load Button images
    Image loadIcon = ImageCache::getFromMemory(BinaryData::loadbutton_png, BinaryData::loadbutton_pngSize);
    loadButton.setImages (false, false, true, loadIcon, 1.0f, {}, loadIcon, 0.8f, {}, loadIcon, 1.0f, {juce::Colours::transparentWhite});
}

/** Constructor for DJAudioPlayer class */
DeckGUI::~DeckGUI()
{
    stopTimer();
}

/** gets called when a region of a component needs redrawing */
void DeckGUI::paint (juce::Graphics& g)
{
    // Draw the background
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    // Draw the border
    g.setColour (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.drawRect (getLocalBounds(), 1);

    // draw jog wheel shadow
    DropShadow jogWheelShadow = DropShadow(Colour(0.0f,0.0f,0.0f,0.15f), 3, Point<int>(2,4));
    Path jogWheel;
    jogWheel.addEllipse(0, (getHeight()/2) + (getHeight()/8)*2, getWidth()/6, getHeight()/8);
    jogWheelShadow.drawForPath(g, jogWheel);
}

/** Called when this component's size has been changed. */
void DeckGUI::resized()
{
    // Setup area dimensions
    double rowH = getHeight()/8;
    double waveformDisplaylArea = getHeight()/2;
    double playbackControlArea = waveformDisplaylArea + (rowH*2);
    double equalizerArea = playbackControlArea + rowH;
    
    // Set bounds of child components
    tapeDeck.setBounds(0, 0, getWidth(), getHeight()/2);
    waveformDisplay.setBounds(0, waveformDisplaylArea, getWidth(), rowH*2);
    equalizer.setBounds(0, equalizerArea, getWidth(), rowH);
    
    // Set button and slider bounds
    double buttonWidth = getWidth()/6;
    speedSlider.setBounds(0, playbackControlArea,  buttonWidth, rowH);
    stopButton.setBounds(buttonWidth, playbackControlArea, buttonWidth, rowH);
    playButton.setBounds(buttonWidth*2, playbackControlArea, buttonWidth, rowH);
    fastforwardButton.setBounds(buttonWidth*3, playbackControlArea, buttonWidth, rowH);
    loopButton.setBounds(buttonWidth*4, playbackControlArea, buttonWidth, rowH);
    loadButton.setBounds(buttonWidth*5, playbackControlArea, buttonWidth, rowH);
}

/** Detects a button click and takes appropriate action depending on button clicked */
void DeckGUI::buttonClicked(Button * button){
    
    // if the pointer for  button is equal to address of play button
    if(button == &playButton){
        if(player->playbackFinished()){
            player->setPosition(0.0);
        }
        player->start();
    }

    if(button == &stopButton){
        player->stop();
    }

    if(button == &loadButton){
        FileChooser chooser{"Select a file"};
        if(chooser.browseForFileToOpen()){
            loadTrack(URL{chooser.getResult()});
        }
    }
    
    if(button == &loopButton){
        player->toggleLoop();
    }
}

/** Detects changes to sliders and updates values */
void DeckGUI::sliderValueChanged(Slider *slider){
    if(slider == &volSlider){
        player->setGain(slider->getValue());
    }

    if(slider == &speedSlider){
        double speed = slider->getValue();
        player->setSpeed(speed);
        // Send speed to tapeDeck component to update tape image
        this->tapeDeck.setSpeed(speed);
    }

    // Removed. Position can now be set on waveform directly
//    if(slider == &posSlider){
//        player->setPositionRelative(slider->getValue());
//    }
}

/** called when slider drag has ended */
void DeckGUI::sliderDragEnded(Slider *slider){
    if(slider == &speedSlider){
        speedSlider.setValue(1.0, sendNotification);
    }
}

/** Callback to check whether this target is interested in the set of files being offered. */
bool DeckGUI::isInterestedInFileDrag (const StringArray &files){
    return true;
}

/** Callback to indicate that the user has dropped the files onto this component. */
void DeckGUI::filesDropped (const StringArray &files, int x, int y){
    // if a single file dropped, load the track
    if(files.size() == 1){
        loadTrack(URL{File{files[0]}});
    }
}

/** user-defined callback routine that gets called periodically */
void DeckGUI::timerCallback(){
    waveformDisplay.setPositionRelative(player->getPositionRelative());
    // set the position for tapedeck
    tapeDeck.setPositionRelative(player->getPositionRelative());
}

/** Loads a track into the deck */
void DeckGUI::loadTrack(URL track){
    player->loadURL(URL{track});
    // Updates the tape title
    this->tapeDeck.setTrackTitle(track.getFileName().toStdString());
    waveformDisplay.loadURL(URL{track});
}

/** detects mouse clicks */
void DeckGUI::mouseDown(const MouseEvent &event){
    if(event.eventComponent == &waveformDisplay){
        double mousePos = event.getMouseDownX();
        double relPos = mousePos / getWidth();
        
        // detects mouse clicks on the waveform and send relative position to player
        player->setPositionRelative(relPos);
    }
    
    if(event.eventComponent == &fastforwardButton){
        if(fastforwardButton.isMouseButtonDown()){
            player->setSpeed(5.0);
        }
    }
    
}

/** detects mouse release */
void DeckGUI::mouseUp(const MouseEvent &event){
    if(event.eventComponent == &fastforwardButton){
        player->setSpeed(1.0);
    }
}
