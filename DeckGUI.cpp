#include <JuceHeader.h>
#include "DeckGUI.h"

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
    
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    
    addAndMakeVisible(waveformDisplay);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(1,100.0);
    posSlider.setRange(0.0, 1.0);
    
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

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("DeckGUI", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    double rowH = getHeight()/8;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    volSlider.setBounds(0, rowH*2, getWidth(), rowH);
    speedSlider.setBounds(0, rowH*3, getWidth(), rowH);
    posSlider.setBounds(0, rowH*4, getWidth(), rowH);
    waveformDisplay.setBounds(0, rowH*5, getWidth(), rowH*2);
    loadButton.setBounds(0, getHeight()-rowH, getWidth(), rowH);

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
    
}

void DeckGUI::sliderValueChanged(Slider *slider){
    if(slider == &volSlider){
        player->setGain(slider->getValue());
    }

    if(slider == &speedSlider){
        player->setSpeed(slider->getValue());
    }

    if(slider == &posSlider){
        player->setPositionRelative(slider->getValue());
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
