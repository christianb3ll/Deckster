/*
 * PlaylistComponent class
 *
 * Displays and manages the playlist
 *
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "AudioTrack.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"

class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public Button::Listener,
                           public TextEditor::Listener,
                           public AudioTransportSource
{
public:
    /** Constructor for PlaylistComponent
     * @param _formatManager - the AudioFormatManager to use
     * @param deck1 - a DeckGUI address
     * @param deck2 - a DeckGUI address */
    PlaylistComponent(AudioFormatManager& _formatManager, DeckGUI* deck1, DeckGUI* deck2);
    
    /** Destructor for PlaylistComponent */
    ~PlaylistComponent() override;
    
    /** Allows the source to release anything it no longer needs after playback has stopped */
    void releaseResources() override;

    /** gets called when a region of a component needs redrawing
     * @param the graphics context that must be used for the drawing operation. */
    void paint (juce::Graphics&) override;
    
    /** Called when this component's size has been changed. */
    void resized() override;
    
    /** returns the number of rows as an int
     * @return numOfRows - int */
    int getNumRows() override;

    /** Draws the row background
     * @param address of a Graphics object
     * @param rowNumber - the row number as int
     * @param width - row width as int
     * @param height - row height as int
     * @param rowIsSelected - bool */
    void paintRowBackground(Graphics &,
                             int rowNumber,
                             int width,
                             int height,
                             bool rowIsSelected) override;

    /** Paints each cell
     * @param address of a Graphics object
     * @param rowNumber - the row number as int
     * @param columnId - the column Id as int
     * @param width - row width as int
     * @param height - row height as int
     * @param rowIsSelected - bool */
    void paintCell(Graphics &,
                   int rowNumber,
                   int columnId,
                   int width,
                   int height,
                   bool rowIsSelected) override;
    
    /** Detects a button click and takes appropriate action depending on button clicked
     * @param Button pointer */
    void buttonClicked(Button* button) override;
    
    /** Adds a given AudioTrack object to the playlist
     * @param track - an AudioTrack object */
    void addToPlaylist(AudioTrack track);
    
    /** called on TextEditor changes
     * @param &searchBar - address of searchBar */
    void textEditorTextChanged(TextEditor &searchBar) override;
    
    /** Converts a given audioURL to an AudioTrack object
     * @param audioURL - a URL to an audio file
     * @return AudioTrack - returns an AudioTrack object */
    AudioTrack URLToAudioTrack(URL audioURL);

    
private:
    AudioFormatManager&  formatManager;
    TableListBox tableComponent;
    
    std::string playlistFilepath = "playlist.csv";
    std::vector<AudioTrack> trackList;
    std::vector<AudioTrack> filteredTracks;
    
    TextButton importButton{"Import a Track"};
    TextButton sendDeck1{"Send to Deck 1"};
    TextButton sendDeck2{"Send to Deck 2"};
    
    TextEditor searchBar{"Search..."};
    
    DeckGUI* deck1;
    DeckGUI* deck2;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
