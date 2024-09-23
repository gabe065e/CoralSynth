/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"
#include "UI/ChorusComponent.h"

//==============================================================================
/**
*/



class CoralSynthAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    CoralSynthAudioProcessorEditor(CoralSynthAudioProcessor&);
    ~CoralSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;



private:

    CoralSynthAudioProcessor& audioProcessor;
    OscComponent osc1;
    OscComponent osc2;
    AdsrComponent adsr;
    ChorusComponent chorus;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CoralSynthAudioProcessorEditor)
};
