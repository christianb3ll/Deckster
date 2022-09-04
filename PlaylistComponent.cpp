#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include "CSVProcessor.h"
#include "AudioTrack.h"

/** Constructor for PlaylistComponent */
PlaylistComponent::PlaylistComponent(AudioFormatManager& _formatManager, DeckGUI* _deck1, DeckGUI* _deck2)
                                    : formatManager(_formatManager),
                                    deck1(_deck1),
                                    deck2(_deck2){
    // import the playlist and populate the trackList
    for(AudioTrack track : CSVProcessor::readCSVFile(playlistFilepath)){
        trackList.push_back(track);
    }
    
    // Initialize the filtered tracklist to be the full tracklist
    filteredTracks = trackList;
                           
    // Create the column headers
    tableComponent.getHeader().addColumn("Track title", 1, 300, TableHeaderComponent::notSortable);
    tableComponent.getHeader().addColumn("Runtime", 2, 100, TableHeaderComponent::notSortable);
    tableComponent.getHeader().addColumn("Sample Rate", 3, 100, TableHeaderComponent::notSortable);
    tableComponent.getHeader().addColumn("File Type", 4, 100, TableHeaderComponent::notSortable);
    tableComponent.getHeader().addColumn("Filepath", 5, 150, TableHeaderComponent::notSortable);
                                        
    tableComponent.setModel(this);
    
    // Add mouse listener to the playlist component
    tableComponent.addMouseListener(this, true);
    
    // Add button listeners
    importButton.addListener(this);
    sendDeck1.addListener(this);
    sendDeck2.addListener(this);
    
    addAndMakeVisible(tableComponent);
    addAndMakeVisible(importButton);
    addAndMakeVisible(searchBar);
    addAndMakeVisible(sendDeck1);
    addAndMakeVisible(sendDeck2);
    
    // Setup the search bar
    searchBar.setTextToShowWhenEmpty("Search Library...", juce::Colours::white);
    textEditorTextChanged(searchBar);
    searchBar.addListener(this);
}

/** Destructor for PlaylistComponent */
PlaylistComponent::~PlaylistComponent()
{
    tableComponent.setModel(nullptr);
}

/** Allows the source to release anything it no longer needs after playback has stopped */
void PlaylistComponent::releaseResources() {
}

/** gets called when a region of a component needs redrawing */
void PlaylistComponent::paint (juce::Graphics& g)
{
    // Draw the background
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    // Draw the border
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);
}

/** Called when this component's size has been changed. */
void PlaylistComponent::resized()
{
    tableComponent.setBounds(0, 50, getWidth(), getHeight()-50);
    importButton.setBounds(0, 0, (getWidth()/6), 50);
    sendDeck1.setBounds((getWidth()/6), 0, (getWidth()/6), 50);
    sendDeck2.setBounds(2*(getWidth()/6), 0, (getWidth()/6), 50);
    searchBar.setBounds(getWidth()/2, 0, getWidth()/2, 50);
}

/** returns the number of rows as an int */
int PlaylistComponent::getNumRows(){
    int playlistRows = static_cast<int>(filteredTracks.size());
    return playlistRows;
}

/** Draws the row background */
void PlaylistComponent::paintRowBackground(Graphics & g, int rowNumber, int width, int height, bool rowIsSelected){
    if(rowIsSelected){
        g.fillAll(Colours::yellow);
    } else {
        g.fillAll(Colours::white);
    }
}

/** Paints each cell */
void PlaylistComponent::paintCell(Graphics & g,  int rowNumber, int columnId, int width, int height, bool rowIsSelected){
    // Track title column
    if(columnId == 1){
        g.drawText(filteredTracks[rowNumber].getTrackTitle(), 2, 0, width - 2, height, Justification::centredLeft, true);
    }
    // Track duration column
    if(columnId == 2){
        g.drawText(filteredTracks[rowNumber].getTrackLength(), 2, 0, width - 2, height, Justification::centredLeft, true);
    }
    // Sample Rate column
    if(columnId == 3){
        g.drawText(filteredTracks[rowNumber].getTrackSampleRate(), 2, 0, width - 2, height, Justification::centredLeft, true);
    }
    // Filepath column
    if(columnId == 4){
        g.drawText(filteredTracks[rowNumber].getTrackType(), 2, 0, width - 2, height, Justification::centredLeft, true);
    }
    
    // Track filepath column
    if(columnId == 5){
        g.drawText(filteredTracks[rowNumber].getTrackFilepath(), 2, 0, width - 2, height, Justification::centredLeft, true);
    }
}

// Removed. Functionality moved to "Send Deck" buttons
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

/** Detects a button click and takes appropriate action depending on button clicked */
void PlaylistComponent::buttonClicked(Button* button){
    if(button == &importButton){
        // Reset the search bar on import
        searchBar.setText("",true);
        
        FileChooser chooser{"Select a file"};
        if(chooser.browseForFileToOpen()){
            
            URL fileURL = chooser.getURLResult();
            // Creat an AudioTrack from URL
            AudioTrack track = URLToAudioTrack(fileURL);
            
            // Add the AudioTrack to the playlist
            addToPlaylist(track);
        }
    }
    // Send to Deck 1
    if(button == &sendDeck1){
        int trackId = tableComponent.getSelectedRow();
        if(trackId != -1){
            deck1->loadTrack(URL{trackList[trackId].getTrackFilepath()});
        }
        
    }
    // Send to Deck 2
    if(button == &sendDeck2){
        int trackId = tableComponent.getSelectedRow();
        if(trackId != -1){
            deck2->loadTrack(URL{trackList[trackId].getTrackFilepath()});
        }
    }
}

/** Adds a given AudioTrack object to the playlist */
void PlaylistComponent::addToPlaylist(AudioTrack track){
    trackList.push_back(track);
    filteredTracks.push_back(track);
    
    // Write the current trackList to CSV file
    CSVProcessor::writeCSVFile(&trackList, playlistFilepath);
    
    // Update the table
    tableComponent.updateContent();
}

/** called on TextEditor changes */
void PlaylistComponent::textEditorTextChanged(TextEditor &searchBar){
    // Clear the filtered tracks list
    filteredTracks.clear();
    
    // filter the tracks
    for(AudioTrack track : trackList){
        if(String(track.getTrackTitle()).contains(searchBar.getText())){
            filteredTracks.push_back(track);
        }
    }
    tableComponent.repaint();
    tableComponent.updateContent();
}

/** Converts a given audioURL to an AudioTrack object */
AudioTrack PlaylistComponent::URLToAudioTrack(URL audioURL){
    // Set up string variables
    std::string trackTitle = audioURL.getFileName().toStdString();
    std::string trackRuntime;
    std::string sampleRate;
    std::string fileType;
    
    double lengthSeconds = 0;
    // create a reader object
    auto* reader = this->formatManager.createReaderFor(audioURL.createInputStream(URL::InputStreamOptions{ URL::ParameterHandling::inAddress }));
    // check for invalid file
    if(reader != nullptr){
        // get the length in seconds
        lengthSeconds = reader->lengthInSamples / reader->sampleRate;
        
        // Convert to minutes / seconds
        int minutes = int(lengthSeconds / 60);
        int seconds = int(lengthSeconds) % 60;
        trackRuntime = std::to_string(minutes) + ":" + std::to_string(seconds);
        
        // get the sample rate
        sampleRate = std::to_string(int(reader->sampleRate));
        
        // https://www.codespeedy.com/get-the-extension-of-a-file-in-cpp
        // store the position of last '.' in the file name
        int pos = int(trackTitle.find_last_of("."));
        //store the characters after the '.' from the file_name string
        fileType = trackTitle.substr(pos+1);

        delete reader;
    }
    
    // create track URL
    std::string trackURL = audioURL.toString(false).toStdString();
    
    // create a new AudioTrack
    AudioTrack track(trackTitle, trackRuntime, sampleRate, fileType, trackURL);
    
    return track;
}
