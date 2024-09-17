/*
  ==============================================================================

    OscData.h
    Created: 16 Sep 2024 5:38:50pm
    Author:  gabe0

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{

public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void setType(const int oscSelection);
    void setGain(const float levelInDecibels);
    void setPitchVal(const int pitch);
    void setFreq(const int midiNoteNumber);
    void renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock);
    void setDrift(const float drift);
    void setFreqInHertz(const float freqInHertz);
    void setSinState(float sinState);
    float getSinState();
    float lfoSin();

private:

    float samplesPerSec = 0.0f;
    float driftNum = 0.0f;
    juce::dsp::Gain<float> gain;
    int pitchVal{ 0 };
    int lastMidiNote{ 0 };
    float sinState = 0.0f;


};

// return std::sin (x); //Sine Wave
// return x / MathConstants<float>::pi; // Saw Wave
// return x < 0.0f ? -1.0f : 1.0f;  // Square Wave