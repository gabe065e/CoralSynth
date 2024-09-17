    /*  
  ==============================================================================

    SynthVoice.cpp
    Created: 16 Sep 2024 4:46:07pm
    Author:  gabe0

  ==============================================================================
*/

#include "SynthVoice.h"


bool synthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void synthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{

    osc1.setFreq(midiNoteNumber);
    osc2.setFreq(midiNoteNumber);
    adsr.noteOn();
}

void synthVoice::stopNote(float velocity, bool allowTailOff)
{
    //hi
    adsr.noteOff();

}


void synthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void synthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}


void synthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int totalNumOutputChannels)
{

    adsr.setSampleRate(sampleRate);



    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = totalNumOutputChannels;

    osc1.prepareToPlay(sampleRate, samplesPerBlock, totalNumOutputChannels);
    osc2.prepareToPlay(sampleRate, samplesPerBlock, totalNumOutputChannels);
    amOsc.prepareToPlay(sampleRate, samplesPerBlock, totalNumOutputChannels);

    gain.prepare(spec);
    gain.setGainLinear(0.2f);




    isPrepared = true;
}


void synthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    //jassert(isPrepared);
    if (!isVoiceActive()) {
        //amOsc.setSinState(0.0f);

        return;
    }


    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };

    osc1.renderNextBlock(audioBlock);
    osc2.renderNextBlock(audioBlock);

    //idkBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    //idkBuffer.clear();

   // juce::dsp::AudioBlock<float> audioBlock2{ idkBuffer };

    //amOsc.renderNextBlock(audioBlock2);

    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());


    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        //outputBuffer.addFrom(channel, startSample, )
        if (!adsr.isActive()) {
            clearCurrentNote();

        }

        auto* buffer = outputBuffer.getWritePointer(channel, 0);
        for (int s = 0; s < outputBuffer.getNumSamples(); ++s)
        {
            juce::Random random;
            outputBuffer.addSample(channel, s, (random.nextFloat() - 0.5) * noise);
            //float oldSample = outputBuffer.getSample(channel, s);

            //sinState = amOsc.getSinState();
            //buffer[s] = oldSample * amOsc.lfoSin();


            //outputBuffer.addSample(channel, s, (random.nextFloat() - 0.5) * lfo);
            //float oldSample = synthBuffer.getSample(channel, s);
            //float newSample = audioBlock2.getSample(channel, s);
            //outputBuffer.setSample(channel, s, oldSample);
        }
    }

}
