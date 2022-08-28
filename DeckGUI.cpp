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
    addAndMakeVisible(rewindButton);
    addAndMakeVisible(fastforwardButton);
    
    addAndMakeVisible(testButton);
    
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
//    addAndMakeVisible(posSlider);
    
    addAndMakeVisible(waveformDisplay);
    
    addAndMakeVisible(equalizer);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    rewindButton.addListener(this);
    fastforwardButton.addListener(this);
    
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
    rewindButton.setBounds(0, playbackControlArea,  buttonWidth, rowH);
    speedSlider.setBounds(buttonWidth, playbackControlArea, buttonWidth, rowH);
    stopButton.setBounds(buttonWidth*2, playbackControlArea, buttonWidth, rowH);
    playButton.setBounds(buttonWidth*3, playbackControlArea, buttonWidth, rowH);
    fastforwardButton.setBounds(buttonWidth*4, playbackControlArea, buttonWidth, rowH);
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
    
    if(button == &rewindButton){
        std::cout << "Rewind Button clicked" << std::endl;
        
    }
    
    if(button == &fastforwardButton){
        std::cout << "Fast Forward Button clicked" << std::endl;
        player->setSpeed(5.0);
    }
    
    if(button == &testButton){
        std::cout << "test Button clicked" << std::endl;
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
