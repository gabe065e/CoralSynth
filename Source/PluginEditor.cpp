/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
CoralSynthAudioProcessorEditor::CoralSynthAudioProcessorEditor(CoralSynthAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), osc1(audioProcessor.apvts, "OSC1", "OSC1GAIN", "OSC1PITCH"), osc2(audioProcessor.apvts, "OSC2", "OSC2GAIN", "OSC2PITCH"), adsr(audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(600, 500);
        

    addAndMakeVisible(adsr);
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
   // THE GRANDMAMA THE BABY



}

CoralSynthAudioProcessorEditor::~CoralSynthAudioProcessorEditor()
{
}

//==============================================================================
void CoralSynthAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::black);

}

void CoralSynthAudioProcessorEditor::resized()
{


    
    osc1.setBounds(0, 25, getWidth() / 2, 100);
    osc2.setBounds(getWidth() / 2, 25, getWidth() / 2, 100);
    adsr.setBounds(0, 125, getWidth(), getHeight() - 125);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}