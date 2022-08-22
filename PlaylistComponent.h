/*
  ==============================================================================

    PlaylistComponent.h
    Created: 5 Aug 2021 4:38:06pm
    Author:  Christian Bell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "AudioTrack.h"
#include "DJAudioPlayer.h"


//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public Button::Listener,
                           public TextEditor::Listener,
                           public AudioTransportSource
{
public:
    PlaylistComponent(AudioFormatManager& _formatManager, DJAudioPlayer* player1, DJAudioPlayer* player2);
    ~PlaylistComponent() override;
    
    void releaseResources() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    int getNumRows() override;

    void paintRowBackground(Graphics &,
                             int rowNumber,
                             int width,
                             int height,
                             bool rowIsSelected) override;

    void paintCell(Graphics &,
                   int rowNumber,
                   int columnId,
                   int width,
                   int height,
                   bool rowIsSelected) override;
    
//    Component*  refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component *existingComponentToUpdate) override;
    
    void buttonClicked(Button* button) override;

    void mouseDoubleClick(const MouseEvent & event) override;
    
    void addToPlaylist(AudioTrack track);
    
    void textEditorTextChanged(TextEditor &searchBar) override;
    
//    void sendToDeck();
    
    AudioTrack URLToAudioTrack(URL audioURL);

    
private:
    AudioFormatManager&  formatManager;
    TableListBox tableComponent;
    
    std::string playlistFilepath = "playlist.csv";
    
    std::vector<AudioTrack> trackList;
    std::vector<int> filteredTracks;
    
    TextButton importButton{"Import a Track"};
//    TextButton openDeck1{"Send to Deck 1"};
//    TextButton openDeck2{"Send to Deck 2"};
    
    TextButton sendDeck1{"Send to Deck 1"};
    TextButton sendDeck2{"Send to Deck 2"};
    
    TextEditor searchBar{"Search..."};
    
    DJAudioPlayer* player1;
    DJAudioPlayer* player2;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
