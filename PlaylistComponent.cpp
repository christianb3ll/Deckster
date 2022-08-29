/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 5 Aug 2021 4:38:06pm
    Author:  Christian Bell

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include "CSVProcessor.h"
#include "AudioTrack.h"


//==============================================================================
PlaylistComponent::PlaylistComponent(AudioFormatManager& _formatManager, DeckGUI* _deck1, DeckGUI* _deck2)
                                    : formatManager(_formatManager),
                                    deck1(_deck1),
                                    deck2(_deck2){
                                        
    for(AudioTrack track : CSVProcessor::readCSVFile(playlistFilepath)){

        // should it check for valid file here?
        trackList.push_back(track);
    }
    
    // Initialize the filtered tracklist to be the full tracklist
    filteredTracks = trackList;
                                        
    tableComponent.getHeader().addColumn("Track title", 1, 300, TableHeaderComponent::notSortable);
    tableComponent.getHeader().addColumn("Runtime", 2, 100, TableHeaderComponent::notSortable);
    tableComponent.getHeader().addColumn("Filepath", 3, 300, TableHeaderComponent::notSortable);
                                        
    tableComponent.setModel(this);
    
    // Add mouse listener to the playlist component
    tableComponent.addMouseListener(this, true);
    
    importButton.addListener(this);
                                        
    sendDeck1.addListener(this);
    sendDeck2.addListener(this);
    
    addAndMakeVisible(tableComponent);
    
    addAndMakeVisible(importButton);
    addAndMakeVisible(searchBar);
    addAndMakeVisible(sendDeck1);
    addAndMakeVisible(sendDeck2);
    
    
    searchBar.setTextToShowWhenEmpty("Search Library...", juce::Colours::white);
    textEditorTextChanged(searchBar);
    
    searchBar.addListener(this);
    
}

PlaylistComponent::~PlaylistComponent()
{
    tableComponent.setModel(nullptr);
}

void PlaylistComponent::releaseResources() {
//    transportSource.releaseResources();
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    tableComponent.setBounds(0, 50, getWidth(), getHeight());
    
    importButton.setBounds(0, 0, (getWidth()/6), 50);
    sendDeck1.setBounds((getWidth()/6), 0, (getWidth()/6), 50);
    sendDeck2.setBounds(2*(getWidth()/6), 0, (getWidth()/6), 50);
    
    searchBar.setBounds(getWidth()/2, 0, getWidth()/2, 50);
}

int PlaylistComponent::getNumRows(){
    int playlistRows = static_cast<int>(filteredTracks.size());
    return playlistRows;
}

void PlaylistComponent::paintRowBackground(Graphics & g, int rowNumber, int width, int height, bool rowIsSelected){
    if(rowIsSelected){
        g.fillAll(Colours::orange);
    } else {
        g.fillAll(Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell(Graphics & g,  int rowNumber, int columnId, int width, int height, bool rowIsSelected){
    // Track title column
    if(columnId == 1){
        g.drawText(filteredTracks[rowNumber].getTrackTitle(), 2, 0, width - 2, height, Justification::centredLeft, true);
    }
    // Track duration column
    if(columnId == 2){
        g.drawText(filteredTracks[rowNumber].getTrackLength(), 2, 0, width - 2, height, Justification::centredLeft, true);
    }
    // Track filepath column
    if(columnId == 3){
        g.drawText(filteredTracks[rowNumber].getTrackFilepath(), 2, 0, width - 2, height, Justification::centredLeft, true);
    }
}

//Component*  PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate){
//    if(columnId == 4){
//        if(existingComponentToUpdate == nullptr){
//            TextButton* btn = new TextButton{"Play Deck 1"};
//            String id{std::to_string(rowNumber)};
//            btn->setComponentID(id);
//            btn->addListener(this);
//            existingComponentToUpdate = btn;
//        }
//    }
//    if(columnId == 5){
//        if(existingComponentToUpdate == nullptr){
//            TextButton* btn = new TextButton{"Play Deck 2"};
//            String id{std::to_string(rowNumber)};
//            btn->setComponentID(id);
//            btn->addListener(this);
//            existingComponentToUpdate = btn;
//        }
//    }
//    return existingComponentToUpdate;
//}

void PlaylistComponent::buttonClicked(Button* button){
    if(button == &importButton){
        // Reset the search bar on import
        searchBar.setText("",true);
        
        std::cout << "import button clicked " << std::endl;
        FileChooser chooser{"Select a file"};
        if(chooser.browseForFileToOpen()){
            
            // check if valid file
            
            // create an AudioTrack object from URL
            
            // send the AudioTrack to the playlist
            
            
            URL fileURL = chooser.getURLResult();
            std::cout << fileURL.toString(false) << std::endl;
            
            AudioTrack track = URLToAudioTrack(fileURL);
            
            std::cout << track.getTrackTitle() << ", " << track.getTrackLength() << std::endl;
            
            addToPlaylist(track);
            
            
            
        }
    }
    if(button == &sendDeck1){
        std::cout << "Send Deck 1" << std::endl;
        int trackId = tableComponent.getSelectedRow();
        
        std::cout << "Track:" << trackId << " selected" << std::endl;
//        player1->loadURL(URL{trackList[trackId].getTrackFilepath()});
//        deck1->player->loadURL(URL{trackList[trackId].getTrackFilepath()});
        deck1->loadTrack(URL{trackList[trackId].getTrackFilepath()});
        
    }
    
    if(button == &sendDeck2){
        std::cout << "Send Deck 2" << std::endl;
        int trackId = tableComponent.getSelectedRow();
        
        std::cout << "Track:" << trackId << " selected" << std::endl;
//        player2->loadURL(URL{trackList[trackId].getTrackFilepath()});
        deck2->loadTrack(URL{trackList[trackId].getTrackFilepath()});
    }
        
//    } else {
//        int id = std::stoi(button->getComponentID().toStdString());
//
//        std::cout << "button clicked " << id << std::endl;
//
//
//        player1->loadURL(URL{trackList[id].getTrackFilepath()});
    
    
}

void PlaylistComponent::addToPlaylist(AudioTrack track){
    trackList.push_back(track);
    filteredTracks.push_back(track);
    
    // Write the current trackList to CSV file
    CSVProcessor::writeCSVFile(&trackList, playlistFilepath);
    
    // Update the table
    tableComponent.updateContent();
}

void PlaylistComponent::textEditorTextChanged(TextEditor &searchBar){
    
    
    std::cout << "Searching: " << searchBar.getText() << std::endl;
    
    filteredTracks.clear();
    
    for(AudioTrack track : trackList){
        if(String(track.getTrackTitle()).contains(searchBar.getText())){
            std::cout << track.getTrackTitle() << std::endl;
            filteredTracks.push_back(track);
        }
    }
    tableComponent.repaint();
    tableComponent.updateContent();
}






AudioTrack PlaylistComponent::URLToAudioTrack(URL audioURL){
    
    // Add a check for valid file
    
    
    std::string trackTitle = audioURL.getFileName().toStdString();
    std::string trackRuntime;
    
    double lengthSeconds = 0;

    auto* reader = this->formatManager.createReaderFor(audioURL.createInputStream(false));

    if(reader != nullptr){
//        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource(reader,true));
//        transportSource.setSource(newSource.get(),0,nullptr, reader->sampleRate);

        lengthSeconds = reader->lengthInSamples / reader->sampleRate;
//        delete reader;

        trackRuntime = std::to_string(lengthSeconds);

//        newSource.reset(newSource.release());
        delete reader;
    }
    
    
    std::string trackURL = audioURL.toString(false).toStdString();
    
    
    
    
    AudioTrack track(trackTitle, trackRuntime, trackURL);
    
    
    return track;
}
