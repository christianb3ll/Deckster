#include <JuceHeader.h>
#include "DeckGUI.h"
#include "Equalizer.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 AudioFormatManager & formatManagerToUse,
                 AudioThumbnailCache & cacheToUse
                 ) : player(_player),
                     waveformDisplay(formatManagerToUse, cacheToUse)
{
    
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
//    addAndMakeVisible(rewindButton);
    addAndMakeVisible(fastforwardButton);
    addAndMakeVisible(loopButton);
    
    addAndMakeVisible(testButton);
    
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
//    addAndMakeVisible(posSlider);
    
    addAndMakeVisible(waveformDisplay);
    
    addAndMakeVisible(equalizer);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
//    rewindButton.addListener(this);
    fastforwardButton.addListener(this);
    loopButton.addListener(this);
    
    testButton.addListener(this);
    
    volSlider.addListener(this);
    speedSlider.addListener(this);
//    posSlider.addListener(this);
    
    // maybe delete
    waveformDisplay.addMouseListener(this, false);

    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(1,20.0);
    speedSlider.setSliderStyle(Slider::Rotary);
    speedSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
//    posSlider.setRange(0.0, 1.0);
    
    startTimer(500);
    
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

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));    // clear the background

    g.setColour (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    // Draw the speaker
    g.setColour(Colour(217, 217, 217));
    g.drawRect(0, 0, getWidth(), getHeight()/6);
    //draw the speaker holes
    g.setColour (juce::Colours::black);
    for (auto i = 0; i < 4; ++i){
        for (auto j = 0; j < 10; ++j){
            g.fillEllipse(getWidth()/3 + (22*j), (getHeight()/6)/3 + (14*i), 10, 10);
        }
    }
//    g.fillEllipse(getWidth()/3, (getHeight()/6)/3, 8, 8);
    
    
    
    // Draw the tapedeck
    g.setColour(Colour(107, 107, 107));
    g.drawRect(0, getHeight()/6, getWidth(), (getHeight()/6)*2);
    
//    g.setColour (juce::Colours::white);
//    g.setFont (14.0f);
//    g.drawText ("DeckGUI", getLocalBounds(),
//                juce::Justification::centred, true);
}

void DeckGUI::resized()
{
    double rowH = getHeight()/8;
    double waveformDisplaylArea = getHeight()/2;
    double playbackControlArea = waveformDisplaylArea + (rowH*2);
    double equalizerArea = playbackControlArea + rowH;
    
    waveformDisplay.setBounds(0, waveformDisplaylArea, getWidth(), rowH*2);
    
    double buttonWidth = getWidth()/6;
    
    speedSlider.setBounds(0, playbackControlArea,  buttonWidth, rowH);
    stopButton.setBounds(buttonWidth, playbackControlArea, buttonWidth, rowH);
    playButton.setBounds(buttonWidth*2, playbackControlArea, buttonWidth, rowH);
    fastforwardButton.setBounds(buttonWidth*3, playbackControlArea, buttonWidth, rowH);
    loopButton.setBounds(buttonWidth*4, playbackControlArea, buttonWidth, rowH);
    loadButton.setBounds(buttonWidth*5, playbackControlArea, buttonWidth, rowH);
    
    
//    volSlider.setBounds(0, rowH*3, getWidth(), rowH);

//    posSlider.setBounds(0, rowH*5, getWidth(), rowH);
   
//    testButton.setBounds(0, rowH*5, getWidth(), rowH);
    
    equalizer.setBounds(0, equalizerArea, getWidth(), rowH);

}

void DeckGUI::buttonClicked(Button * button){
    
    // if the pointer for  button is equal to address of play button
    if(button == &playButton){
        std::cout << "Play Button clicked" << std::endl;
        player->start();
    }

    if(button == &stopButton){
        std::cout << "Stop Button clicked" << std::endl;
        player->stop();
    }

    if(button == &loadButton){
        std::cout << "Load Button clicked" << std::endl;
        FileChooser chooser{"Select a file"};
        if(chooser.browseForFileToOpen()){
//            player->loadURL(URL{chooser.getResult()});
//            waveformDisplay.loadURL(URL{chooser.getResult()});
            loadTrack(URL{chooser.getResult()});
        }

    }
    
//    if(button == &rewindButton){
//        std::cout << "Rewind Button clicked" << std::endl;
//
//    }
    
    if(button == &fastforwardButton){
        std::cout << "Fast Forward Button clicked" << std::endl;
        player->setSpeed(5.0);
    }
    
    if(button == &testButton){
        std::cout << "test Button clicked" << std::endl;
        player->toggleLoop();
    }
    
    if(button == &loopButton){
        std::cout << "loop Button clicked" << std::endl;
        player->toggleLoop();
    }
    
}

void DeckGUI::sliderValueChanged(Slider *slider){
    if(slider == &volSlider){
        player->setGain(slider->getValue());
    }

    if(slider == &speedSlider){
        player->setSpeed(slider->getValue());
    }

    // Removed. Position can now be set on waveform directly
//    if(slider == &posSlider){
//        player->setPositionRelative(slider->getValue());
//    }
}

void DeckGUI::sliderDragEnded(Slider *slider){
    if(slider == &speedSlider){
        speedSlider.setValue(1.0, sendNotification);
    }
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files){
    return true;
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y){
    
    std::cout << "file dropped" << std::endl;
    if(files.size() == 1){
//        player->loadURL(URL{File{files[0]}});
//        waveformDisplay.loadURL(URL{File{files[0]}});
        loadTrack(URL{File{files[0]}});
    }
}

void DeckGUI::timerCallback(){
    waveformDisplay.setPositionRelative(player->getPositionRelative());
}

void DeckGUI::loadTrack(URL track){
    player->loadURL(URL{track});
    waveformDisplay.loadURL(URL{track});
}


void DeckGUI::mouseDown(const MouseEvent &event){
    double mousePos = event.getMouseDownX();
    double relPos = mousePos / getWidth();
    std::cout << relPos << std::endl;
    
    player->setPositionRelative(relPos);
}
