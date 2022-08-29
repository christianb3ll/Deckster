/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 15 Jul 2021 10:26:17pm
    Author:  Christian Bell

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager)
                            : formatManager(_formatManager){
}

DJAudioPlayer::~DJAudioPlayer(){
}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate) {
  
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    filterSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) {
//    resampleSource.getNextAudioBlock(bufferToFill);
    filterSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
    filterSource.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL){
    auto* reader = this->formatManager.createReaderFor(audioURL.createInputStream(URL::InputStreamOptions{ URL::ParameterHandling::inAddress }));
    
    
    if(reader != nullptr){
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource(reader,true));
        transportSource.setSource(newSource.get(),0,nullptr, reader->sampleRate);
        
        std::cout << "Loaded URL" << std::endl;
        
//        std::cout << reader->metadataValues.getAllKeys().size() << std::endl;
        
//        for (String key : reader->metadataValues.getAllKeys()) {
//            std::cout << "Key: " + key + " value: " + reader->metadataValues.getValue(key, "unknown") << std::endl;
//        }
//
//
        readerSource.reset(newSource.release());
        
    }
    else {
        std::cout << "Invalid URL" << std::endl;
    }
}

void DJAudioPlayer::setGain(double gain){
    if(gain < 0 || gain > 1.0){
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    } else {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setSpeed(double ratio){
    if(ratio <= 0 || ratio > 100.0){
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
    } else {
        resampleSource.setResamplingRatio(ratio);
    }
}

void DJAudioPlayer::setPosition(double posInSecs){
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos){
    if(pos < 0 || pos > 1.0){
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 1" << std::endl;
    } else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

void DJAudioPlayer::start(){
    transportSource.start();
}

void DJAudioPlayer::stop(){
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative(){
    if(transportSource.getLengthInSeconds() == 0){
        return 0;
    } else {
        return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
    }
}


//std::string DJAudioPlayer::getTrackRuntime(URL audioURL){
//    std::string trackRuntime;
//    
//    
//    double lengthSeconds = 0;
//    
//    auto* reader = this->formatManager.createReaderFor(audioURL.createInputStream(false));
//    
//    if(reader != nullptr){
//        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource(reader,true));
//        transportSource.setSource(newSource.get(),0,nullptr, reader->sampleRate);
//    
//        lengthSeconds = reader->lengthInSamples / reader->sampleRate;
//        delete reader;
//    
//        trackRuntime = std::to_string(lengthSeconds);
//        
//        
//    }
//    
//
//    return trackRuntime;
//}


void DJAudioPlayer::test(){
    std::cout << "I'm here" << std::endl;
}

//readerSource->setLooping(true);
void DJAudioPlayer::toggleLoop(){
    // toggle track looping on/off
    readerSource->setLooping(!looping);
}

void DJAudioPlayer::setFilterCoefficients(IIRCoefficients coefficients){
    filterSource.setCoefficients(coefficients);
}
