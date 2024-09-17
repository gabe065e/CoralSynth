/*
  ==============================================================================

    OscComponent.h
    Created: 16 Sep 2024 5:39:05pm
    Author:  gabe0

  ==============================================================================
*/


#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String oscId, juce::String gainId, juce::String pitchId);
    ~OscComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox oscSelector;
    juce::Slider gainSlider;
    juce::Slider pitchSlider;
    juce::Label waveSelectorLabel{ "Wave Type", "Wave Type" };
    juce::ColourGradient gd;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pitchAttachment;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscComponent)
};