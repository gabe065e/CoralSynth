/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
CoralSynthAudioProcessor::CoralSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{

    synth.addSound(new synthSound());

    for (int i = 0; i < 5; i++)
    {
        synth.addVoice(new synthVoice());
    }




}

CoralSynthAudioProcessor::~CoralSynthAudioProcessor()
{
}

//==============================================================================
const juce::String CoralSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CoralSynthAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool CoralSynthAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool CoralSynthAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double CoralSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CoralSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int CoralSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CoralSynthAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String CoralSynthAudioProcessor::getProgramName(int index)
{
    return {};
}

void CoralSynthAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void CoralSynthAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<synthVoice*>(synth.getVoice(i))) {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }

}

void CoralSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CoralSynthAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void CoralSynthAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());


    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<synthVoice*>(synth.getVoice(i)))
        {

            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            auto& osc1Choice = *apvts.getRawParameterValue("OSC1");
            auto& osc2Choice = *apvts.getRawParameterValue("OSC2");
            auto& osc1Gain = *apvts.getRawParameterValue("OSC1GAIN");
            auto& osc2Gain = *apvts.getRawParameterValue("OSC2GAIN");
            auto& osc1Pitch = *apvts.getRawParameterValue("OSC1PITCH");
            auto& osc2Pitch = *apvts.getRawParameterValue("OSC2PITCH");
            auto& noise = *apvts.getRawParameterValue("NOISE");
            auto& drift = *apvts.getRawParameterValue("DRIFT");

            auto& osc1 = voice->getOscillator1();
            auto& osc2 = voice->getOscillator2();
            auto& amOsc = voice->getAMosc();

            auto& adsr = voice->getAdsr();

            //amOsc.setType(0);
            //amOsc.setGain(osc1Gain);
            //amOsc.setFreqInHertz(1.0f);


            voice->setNoise(noise);

            osc1.setType(osc1Choice);
            osc1.setDrift(drift);
            osc1.setGain(osc1Gain);
            osc1.setPitchVal(osc1Pitch);


            osc2.setType(osc2Choice);
            osc2.setGain(osc2Gain);
            osc2.setPitchVal(osc2Pitch);



            adsr.update(attack.load(), decay.load(), sustain.load(), release.load());



        }

    }


    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool CoralSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CoralSynthAudioProcessor::createEditor()
{
    return new CoralSynthAudioProcessorEditor(*this);
}

//==============================================================================
void CoralSynthAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CoralSynthAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CoralSynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout CoralSynthAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1", "Oscillator 1", juce::StringArray{ "Sine", "Saw", "Square" }, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC2", "Oscillator 2", juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    // OSC Gain
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1GAIN", "Oscillator 1 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f, }, 0.1f, "dB"));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2GAIN", "Oscillator 2 Gain", juce::NormalisableRange<float> { -40.0f, 0.2f, 0.1f}, 0.1f, "dB"));

    // OSC Pitch val
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC1PITCH", "Oscillator 1 Pitch", -24, 24, 0));
    params.push_back(std::make_unique<juce::AudioParameterInt>("OSC2PITCH", "Oscillator 2 Pitch", -24, 24, 0));

    // ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f,}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.0f, 1.0f, 0.01f,}, 0.4f));

    // NOISE
    params.push_back(std::make_unique<juce::AudioParameterFloat>("NOISE", "Noise", juce::NormalisableRange<float> {0.0f, 0.1f, 0.01f,}, 0.0f));

    // DRIFT??
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DRIFT", "Drift", juce::NormalisableRange<float> {0.0f, 1.0f, 0.01f,}, 0.0f));


    return { params.begin(), params.end() };
}

//==============================================================================


// Value Tree
