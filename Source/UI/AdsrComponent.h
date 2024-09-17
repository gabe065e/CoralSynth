/*
  ==============================================================================

    AdsrComponent.h
    Created: 16 Sep 2024 5:36:58pm
    Author:  gabe0

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AdsrComponent : public juce::Component
{
public:
    AdsrComponent(juce::AudioProcessorValueTreeState& apvts);
    ~AdsrComponent() override;
    void paint(juce::Graphics&) override;
    void resized() override;
private:
    void setSliderParams(juce::Slider& slider);
    void setSliderParamsVariant(juce::Slider& slider);
    void setRotaryParams(juce::Slider& slider);

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    juce::Slider noiseSlider;
    juce::Slider driftSlider;

    juce::Label driftLabel{ "Drift", "Drift" };
    juce::Label noiseLabel{ "Noise", "Noise" };


    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    std::unique_ptr<SliderAttachment> noiseAttachment;
    std::unique_ptr<SliderAttachment> driftAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AdsrComponent)
};