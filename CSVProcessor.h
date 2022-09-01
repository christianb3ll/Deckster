/*
 * CSVProcessor class
 *
 * A helper class that handles all operations relating to reading
 * and writing of CSV files
 *
*/

#include <vector>
#include <string>
#include "AudioTrack.h"

#pragma once

class CSVProcessor {
    public:
        /** Constructor for CSVProcessor class */
        CSVProcessor();
    
        /** Destructor for CSVProcessor class */
        ~CSVProcessor();
        
        /** returns a vector of AudioTrack objects from a given CSV file URL
         * @param csvFilename - a string URL to a CSV file
         * @return vector - a vector of AudioTrack objects */
        static std::vector<AudioTrack> readCSVFile(std::string csvFilename);
    
        /** attempts to write XXXXX to a given CSV file and returns a boolean
         * @param
         * @return */
        static void writeCSVFile(std::vector<AudioTrack>* tracks, std::string playlist);
    
        
        
    
        /** Converts a string to tokens based on a given seperator
         * @param csvLine a string representing a line from a csv file
         * @param separator a seperator char, eg "," "/"
         * @return vector returns a vector of strings */
        static std::vector<std::string> tokenize(std::string csvLine, char separator);
    private:
};
