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
                std::string filepath = trackTokens[2];
                
                // create an audio track object
                AudioTrack track{title,runtime,filepath};
                
                std::cout << "Track details are: " + title + ", " + runtime + ", " + filepath  << std::endl;
                
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



void CSVProcessor::writeCSVFile(std::vector<AudioTrack>* tracks, std::string playlist){
    std::ofstream CSVFile(playlist, std::ios::trunc);
    if (CSVFile.is_open())
      {
          for(AudioTrack track : *tracks){
              std::string trackName = track.getTrackTitle();
              std::string runtime = track.getTrackLength();
              std::string filepath = track.getTrackFilepath();

              CSVFile << trackName << "," << runtime << "," << filepath << "\n";
          }
          CSVFile.close();
          std::cout << "csv file written" << std::endl;
      }
    else {
        std::cout << "Unable to write file" << std::endl;
    }
}


//void CSVProcessor::writeVectorTest(std::vector<AudioTrack>* tracks, std::string playlist){
//    std::ofstream CSVFile(playlist, std::ios::trunc);
//    if (CSVFile.is_open())
//      {
//          for(AudioTrack track : *tracks){
//              std::string trackName = track.getTrackTitle();
//              std::string runtime = track.getTrackLength();
//              std::string filepath = track.getTrackFilepath();
//
//              CSVFile << trackName << ", " << runtime << ", " << filepath << "\n";
//          }
//          CSVFile.close();
//          std::cout << "csv file written" << std::endl;
//      }
//    else {
//        std::cout << "Unable to write file" << std::endl;
//    }
//}




bool CSVProcessor::writeTest(std::string trackName, std::string trackDuration, std::string filepath, std::string playlist){
    std::ofstream CSVFile(playlist, std::ios::trunc);
    if (CSVFile.is_open())
      {
          CSVFile << trackName << "," << trackDuration << "," << filepath << "\n";
          
          CSVFile.close();
          std::cout << "csv file written" << std::endl;
          
          return true;
      }
    else {
        std::cout << "Unable to write file" << std::endl;
        return false;
    }
        
}







/** Converts a string to tokens based on a given seperator */
std::vector<std::string> CSVProcessor::tokenize(std::string csvLine, char separator){
    std::vector<std::string> tokens;
    std::string token;
    
    signed int start, end;
    start = csvLine.find_first_not_of(separator,0);
    
    do {
        end = csvLine.find_first_of(separator, start);
        if(start == csvLine.length() || start == end) break;
        if(end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    } while(end > 0);
    
    return tokens;
};


