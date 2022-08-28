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
    speedSlider.setRange(1,100.0);
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

    g.fillAll (Colour(169,169,169));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    // Draw the speaker
    
    
    // Draw the tapedeck
    
//    g.setColour (juce::Colours::white);
//    g.setFont (14.0f);
//    g.drawText ("DeckGUI", getLocalBounds(),
//                juce::Justification::centred, true);
}

void DeckGUI::resized()
{
    double rowH = getHeight()/8;
    
    waveformDisplay.setBounds(0, 0, getWidth(), rowH*2);
    
    rewindButton.setBounds(0, rowH*2, getWidth()/5, rowH);
    stopButton.setBounds(getWidth()/5, rowH*2, getWidth()/5, rowH);
    playButton.setBounds((getWidth()/5)*2, rowH*2, getWidth()/5, rowH);
    fastforwardButton.setBounds((getWidth()/5)*3, rowH*2, getWidth()/5, rowH);
    loadButton.setBounds((getWidth()/5)*4, rowH*2, getWidth()/5, rowH);
    
    
    volSlider.setBounds(0, rowH*3, getWidth(), rowH);
    speedSlider.setBounds(0, rowH*4, getWidth(), rowH);
//    posSlider.setBounds(0, rowH*5, getWidth(), rowH);
   
    testButton.setBounds(0, rowH*5, getWidth(), rowH);
    
    equalizer.setBounds(0, rowH*6, getWidth(), rowH*2);

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
