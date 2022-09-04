#include "DJAudioPlayer.h"

/** Consttructor for DJAudioPlayer */
DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager)
                            : formatManager(_formatManager){
}

/** Destructor for DJAudioPlayer */
DJAudioPlayer::~DJAudioPlayer(){
}

/** Tells the source to prepare for playing */
void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate) {
  
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    // prepare the filters
    filter1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    filter2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
}

/** Called repeatedly to fetch subsequent blocks of audio data */
void DJAudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) {
    filter2.getNextAudioBlock(bufferToFill);
}

/** Allows the source to release anything it no longer needs after playback has stopped */
void DJAudioPlayer::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
    filter1.releaseResources();
    filter2.releaseResources();
}

/** loads a given audio URL */
void DJAudioPlayer::loadURL(URL audioURL){
    // Updated - previous version deprecated
    auto* reader = this->formatManager.createReaderFor(audioURL.createInputStream(URL::InputStreamOptions{ URL::ParameterHandling::inAddress }));
    
    if(reader != nullptr){
        std::unique_ptr<AudioFormatReaderSource> newSource (new AudioFormatReaderSource(reader,true));
        transportSource.setSource(newSource.get(),0,nullptr, reader->sampleRate);
        // set the current sample rate
        this->currentSampleRate = reader->sampleRate;
        // Set the current track name
        this->currentTrack = audioURL.getFileName().toStdString();
        readerSource.reset(newSource.release());
    }
    else {
        std::cout << "Invalid URL" << std::endl;
    }
}

/** sets the gain for the player */
void DJAudioPlayer::setGain(double gain){
    if(gain < 0 || gain > 1.0){
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    } else {
        transportSource.setGain(gain);
    }
}

/** sets the speed for the player */
void DJAudioPlayer::setSpeed(double ratio){
    if(ratio <= 0 || ratio > 100.0){
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
    } else {
        resampleSource.setResamplingRatio(ratio);
    }
}

/** sets the position */
void DJAudioPlayer::setPosition(double posInSecs){
    transportSource.setPosition(posInSecs);
}

/** sets the relative position */
void DJAudioPlayer::setPositionRelative(double pos){
    if(pos < 0 || pos > 1.0){
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 1" << std::endl;
    } else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

/** start the transport source */
void DJAudioPlayer::start(){
    transportSource.start();
}

/** stop the transport source */
void DJAudioPlayer::stop(){
    transportSource.stop();
}

/** Get the relative position of the playhead */
double DJAudioPlayer::getPositionRelative(){
    if(transportSource.getLengthInSeconds() == 0){
        return 0;
    } else {
        return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
    }
}

/** get the current track title */
std::string DJAudioPlayer::getCurrentTrack(){
    return this->currentTrack;
}

/** set the current track title */
void DJAudioPlayer::setCurrentTrack(std::string title){
    this->currentTrack = title;
}

/** get the current track sample rate */
int DJAudioPlayer::getCurrentSampleRate(){
    return this->currentSampleRate;
}

/** set the current track sample rate  */
void DJAudioPlayer::setCurrentSampleRate(int sampleRate){
    this->currentSampleRate = sampleRate;
}

/** toggles looping playback */
void DJAudioPlayer::toggleLoop(){
    if(readerSource != nullptr){
        // toggle track looping on/off
        this->looping = !looping;
        readerSource->setLooping(looping);
    }
}

/** checks if the transport source is playing */
bool DJAudioPlayer::isPlaying(){
    return this->transportSource.isPlaying();
}

/** checks if the transport source is looping  */
bool DJAudioPlayer::isLooping(){
    return this->looping;
}

/** checks if the transport source has finished */
bool DJAudioPlayer::playbackFinished(){
    return this->transportSource.hasStreamFinished();
}

/** sets coefficients for the HighPass filter */
void DJAudioPlayer::setHighPassCoefficients(IIRCoefficients coefficients){
    filter1.setCoefficients(coefficients);
}

/** sets coefficients for the LowPass filter */
void DJAudioPlayer::setLowPassCoefficients(IIRCoefficients coefficients){
    filter2.setCoefficients(coefficients);
}

/** deactivates given filter */
void DJAudioPlayer::deactivateFilter(std::string filter){
    if(filter == "highPass"){
        filter1.makeInactive();
    }
    
    if(filter == "lowPass"){
        filter2.makeInactive();
    }
    
}
