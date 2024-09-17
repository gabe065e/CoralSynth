/*
  ==============================================================================

    SynthVoice.h
    Created: 16 Sep 2024 4:46:07pm
    Author:  gabe0

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/AdsrData.h"
#include "Data/OscData.h"



class synthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound*) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int totalNumOutputChannels);
    void renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;
    OscData& getOscillator1() { return osc1; }
    OscData& getOscillator2() { return osc2; }
    OscData& getAMosc() { return amOsc; }
    AdsrData& getAdsr() { return adsr; }
    float getNoise() { return noise; }
    void setNoise(float noiseVal) { noise = noiseVal; }


private:

    OscData osc1;
    OscData osc2;
    OscData amOsc;
    OscData somethingElse;
    AdsrData adsr;
    juce::AudioBuffer<float> synthBuffer;
    //juce::AudioBuffer<float> idkBuffer;
    float noise = 0.0f;
    //float sinState = 0.0f;

    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };

};