/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 15 Jul 2021 10:26:17pm
    Author:  Christian Bell

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DJAudioPlayer : public AudioSource {
    public:
        DJAudioPlayer(AudioFormatManager& _formatManager);
        ~DJAudioPlayer();
    
        void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;
    
        void loadURL(URL audioURL);
        void setGain(double gain);
        void setSpeed(double ratio);
        void setPosition(double posInSecs);
        void setPositionRelative(double pos);
        
        void start();
        void stop();
    
        /** Get the relative position of the playhead */
        double getPositionRelative();
        
    
        void toggleLoop();
    
        void setFilterCoefficients(IIRCoefficients coefficients);
    
    private:
        AudioFormatManager&  formatManager;
        std::unique_ptr<AudioFormatReaderSource> readerSource;
        AudioTransportSource transportSource;
        ResamplingAudioSource resampleSource{&transportSource, false, 2};
        IIRFilterAudioSource filterSource{&resampleSource, false};
        bool looping = false;
};
