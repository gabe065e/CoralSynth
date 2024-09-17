/*
  ==============================================================================

    OscData.cpp
    Created: 16 Sep 2024 5:38:50pm
    Author:  gabe0

  ==============================================================================
*/


#include "OscData.h"
#define pi juce::MathConstants<float>::pi


void OscData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    samplesPerSec = sampleRate;
    prepare(spec);
    gain.prepare(spec);

}

void OscData::setType(const int oscSelection)
{
    switch (oscSelection)
    {
        // Sine
    case 0:
        initialise([](float x) { return std::sin(x); });
        //initialise([](float x) { juce::Random random; return random.nextFloat();});
        break;

        // Saw
    case 1:
        //initialise([](float x) {float sum = 0.0f; for (int i = 1; i < 50; ++i) { sum = sum + (std::sin(i * x) / i); } return sum; });
        //initialise([](float x) { return x / juce::MathConstants<float>::pi; });
        //initialise([](float x) { return ( - x / juce::MathConstants<float>::pi); });

        initialise([](float x) {
            float delta = 0.04f;
            float sqr = 2 * std::atan(std::sin(2 * pi * ((x / (2 * pi)) / 2)) / delta) / pi;
            float trg = 1 - (2 * std::acos((1 - delta) * std::sin(2 * pi * (2 * (x / (2 * pi)) - 1) / 4)) / pi);
            return ((1 + trg * sqr) / 2) - 0.5f; });
        break;

        // Square
    case 2:
        initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; });
        break;

    default:

        jassertfalse;
        break;
    }
}

void OscData::setGain(const float levelInDecibels)
{
    gain.setGainDecibels(levelInDecibels);
}

void OscData::setPitchVal(const int pitch)
{

    pitchVal = pitch;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote + pitchVal) + driftNum);
}

void OscData::setFreq(const int midiNoteNumber)
{

    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + pitchVal));
    lastMidiNote = midiNoteNumber;
}

void OscData::setFreqInHertz(const float freqInHertz)
{
    setFrequency(freqInHertz);
}

void OscData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock)
{
    jassert(audioBlock.getNumSamples() > 0);
    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

}

void OscData::setDrift(float drift) {
    driftNum = drift;
}


float OscData::lfoSin() {

    sinState = sinState + (getFrequency() / samplesPerSec);
    return std::sin(sinState);
}

void OscData::setSinState(float x) {
    sinState = x;
}
float OscData::getSinState() {
    return sinState;
    // hi
}
