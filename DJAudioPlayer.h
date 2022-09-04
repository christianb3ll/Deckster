/*
 * DJAudioPlayer class
 *
 * handles playback of audio files
 *
*/

#pragma once
#include <JuceHeader.h>

class DJAudioPlayer : public AudioSource {
    public:
        /** Consttructor for DJAudioPlayer
         * @param _formatManager - the format manager to use */
        DJAudioPlayer(AudioFormatManager& _formatManager);
    
        /** Destructor for DJAudioPlayer */
        ~DJAudioPlayer();
        
        /** Tells the source to prepare for playing
         * @param samplesPerBlockExpected - number of samples expected each time getNextAudioBlock() called
         * @param sampleRate - the sample rate */
        void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    
        /** Called repeatedly to fetch subsequent blocks of audio data
         * @param bufferToFill */
        void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    
        /** Allows the source to release anything it no longer needs after playback has stopped */
        void releaseResources() override;
    
        /** loads a given audio URL
         * @param audioURL - an audio file URL*/
        void loadURL(URL audioURL);
    
        /** sets the gain for the player
         * @param gain - gain as double */
        void setGain(double gain);
    
        /** sets the speed for the player
         * @param ratio - speed ratio as double */
        void setSpeed(double ratio);
    
        /** sets the position
         * @param posInSecs -double  position in seconds*/
        void setPosition(double posInSecs);

        /** sets the relative position
         * @param pos - double relative position*/
        void setPositionRelative(double pos);
        
        /** start the transport source */
        void start();
    
        /** stop the transport source */
        void stop();
    
        /** Get the relative position of the playhead
         * @return double - relative position */
        double getPositionRelative();
    
        /** get the current track title
         * @return String - current track title */
        std::string getCurrentTrack();
    
        /** set the current track title
         * @param String - current track title */
        void setCurrentTrack(std::string title);
    
        /** get the current track sample rate
         * @return int - current sample rate */
        int getCurrentSampleRate();

        /** set the current track sample rate
         * @param int - sample rate */
        void setCurrentSampleRate(int sampleRate);
    
        /** toggles looping playback */
        void toggleLoop();
    
        /** checks if the transport source has finished
         * @return bool */
        bool playbackFinished();
    
        /** sets coefficients for the HighPass filter
         * @param coefficients - IIRCoefficients object */
        void setHighPassCoefficients(IIRCoefficients coefficients);
    
        /** sets coefficients for the LowPass filter
         * @param coefficients - IIRCoefficients object */
        void setLowPassCoefficients(IIRCoefficients coefficients);
        
        /** deactivates given filter
         * @param filter - filter name as string */
        void deactivateFilter(std::string filter);
    
    private:
        AudioFormatManager&  formatManager;
        std::unique_ptr<AudioFormatReaderSource> readerSource;
        AudioTransportSource transportSource;
        ResamplingAudioSource resampleSource{&transportSource, false, 2};
        // Filters
        IIRFilterAudioSource filter1{&resampleSource, false};
        IIRFilterAudioSource filter2{&filter1, false};
    
        std::string currentTrack;
        int currentSampleRate;
        bool looping = false;
};
