/*
 * AudioTrack class
 *
 * AudioTrack obects contain data related to an individual audio track
 * along with get methods to retrive track metadata
*/

#include <string>
#include <JuceHeader.h>


#pragma once

class AudioTrack {
    public:
        /** constructor creates a new AudioTrack with given values
         * @param _trackTitle - string representing track title
         * @param _trackLength - string representing track length
         * @param _trackSampleRate - string representing track sample length
         * @param _trackType - string representing track type
         * @param _filepath - string track filepath   */
        AudioTrack(std::string _trackTitle,
                   std::string _trackLength,
                   std::string _sampleRate,
                   std::string _fileType,
                   std::string _filepath);
        
        /** Destructor for AudioTrack class */
        ~AudioTrack();
    
        /** returns the track title as a string
         * @return string track title */
        std::string getTrackTitle();
    
        /** returns the track length as a string
         * @return string track length */
        std::string getTrackLength();
    
        /** returns the tracks sample rate as a string
         * @return string track sample rate */
        std::string getTrackSampleRate();
        
        /** returns the track type as a string
         * @return string track type */
        std::string getTrackType();
    
        /** returns the track filepath as a string
         * @return String track filepath */
        std::string getTrackFilepath();
        
        /** converts a given AudioTrack object to a comma seperated string
         * @param track AudioTrack object
         * @return string of comma seperated AudioTrack details  */
        std::string toString();
    
    private:
        std::string trackTitle;
        std::string trackLength;
        std::string sampleRate;
        std::string fileType;
        std::string filepath;

};
