#include "CSVProcessor.h"
#include <iostream>
#include <fstream>
#include "PlaylistComponent.h"

/** Constructor for CSVProcessor class */
CSVProcessor::CSVProcessor(){
};

/** returns a vector of AudioTrack objects from a given CSV file URL */
std::vector<AudioTrack> CSVProcessor::readCSVFile(std::string csvFilename){
    // Create a new file input stream
    std::ifstream CSVFile(csvFilename);
    std::string line;
    std::vector<AudioTrack> tracks;
    
    // Check the file is open
    if(CSVFile.is_open()){
        // Get each line of the file, each line representing a new track
        while(std::getline(CSVFile,line)){
            // Attempt to read track data
            try{
                // tokenize the input
                std::vector<std::string> trackTokens = tokenize(line, ',');
                
                // Create strings for each token
                std::string title = trackTokens[0];
                std::string runtime = trackTokens[1];
                std::string sampleRate = trackTokens[2];
                std::string fileType = trackTokens[3];
                std::string filepath = trackTokens[4];
                
                // create an audio track object
                AudioTrack track{title,runtime,sampleRate,fileType,filepath};
                
                // Add the AudioTrack to the tracklist
                tracks.push_back(track);

            // catch improperly formatted data
            } catch(const std::exception& e) {
                std::cout << "Bad data" << std::endl;
            }
        }
        // close the file
        CSVFile.close();
        
        return tracks;
    // If the file is not / could not be opened
    } else {
        std::cout << "Failed to open file " << csvFilename << std::endl;
        
        return tracks;
    }
}

/** attempts to write a vecotr of AudioTrack objects to a given CSV filepath */
void CSVProcessor::writeCSVFile(std::vector<AudioTrack>* tracks, std::string playlist){
    std::ofstream CSVFile(playlist, std::ios::trunc);
    if (CSVFile.is_open())
      {
          for(AudioTrack track : *tracks){
              std::string trackName = track.getTrackTitle();
              std::string runtime = track.getTrackLength();
              std::string sampleRate = track.getTrackSampleRate();
              std::string fileType = track.getTrackType();
              std::string filepath = track.getTrackFilepath();

              CSVFile << trackName << "," << runtime << "," << sampleRate << "," << fileType << "," << filepath << "\n";
          }
          CSVFile.close();
      }
    else {
        std::cout << "Unable to write file" << std::endl;
    }
}

/** Converts a string to tokens based on a given seperator */
std::vector<std::string> CSVProcessor::tokenize(std::string csvLine, char separator){
    std::vector<std::string> tokens;
    std::string token;
    
    signed int start, end;
    start = int(csvLine.find_first_not_of(separator,0));
    
    do {
        end = int(csvLine.find_first_of(separator, start));
        if(start == csvLine.length() || start == end) break;
        if(end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    } while(end > 0);
    
    return tokens;
};


