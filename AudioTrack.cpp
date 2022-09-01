#include "AudioTrack.h"

/** constructor creates a new AudioTrack with given values */
AudioTrack::AudioTrack(std::string _trackTitle,
                       std::string _trackLength,
                       std::string _sampleRate,
                       std::string _fileType,
                       std::string _filepath)
: trackTitle(_trackTitle),
  trackLength(_trackLength),
  sampleRate(_sampleRate),
  fileType(_fileType),
  filepath(_filepath)
{
    
}

/** Destructor for AudioTrack class */
AudioTrack::~AudioTrack(){
    
}

/** returns the track title as a string */
std::string AudioTrack::getTrackTitle(){
    return this->trackTitle;
}

/** returns the track length as a string */
std::string AudioTrack::getTrackLength(){
    return this->trackLength;
}

/** returns the tracks sample rate as a string */
std::string AudioTrack::getTrackSampleRate(){
    return this->sampleRate;
}

/** returns the track type as a string */
std::string AudioTrack::getTrackType(){
    return this->fileType;
}

/** returns the track filepath URL  */
std::string AudioTrack::getTrackFilepath(){
    return filepath;
}

/** converts a given AudioTrack object to a string */
std::string AudioTrack::toString(){
    // create a new string
    std::string trackString;
    
    // create a comma seperated string of AudioTrack metadata - Title, Length, Filepath
    trackString = this->getTrackTitle() + ", " + this->getTrackLength() + ", " + this->getTrackSampleRate() + ", " + this->getTrackType() + ", " + this->getTrackFilepath();
    
    return trackString;
}
