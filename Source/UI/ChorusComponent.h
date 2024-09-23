/*
  ==============================================================================

    ChorusComponent.h
    Created: 20 Sep 2024 12:31:42pm
    Author:  gabe0

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ChorusComponent  : public juce::Component
{
public:
    ChorusComponent(juce::AudioProcessorValueTreeState& apvts);
    ~ChorusComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    void setRotaryParams(juce::Slider& slider);
    void setLabelParams(juce::Label& label);

    juce::Slider centreDelaySlider;
    juce::Slider rateSlider;
    juce::Slider depthSlider;
    juce::Slider feedbackSlider;
    juce::Slider mixSlider;

    juce::Label rateLabel{ "Rate", "Rate" };
    juce::Label depthLabel{ "Depth", "Depth" };
    juce::Label feedbackLabel{ "Feedback", "Feedback" };
    juce::Label mixLabel{ "Mix", "Mix" };
    juce::Label centreDelayLabel{ "Centre Delay", "Centre Delay" };

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr<SliderAttachment> centreDelayAttachment;
    std::unique_ptr<SliderAttachment> rateAttachment;
    std::unique_ptr<SliderAttachment> depthAttachment;
    std::unique_ptr<SliderAttachment> feedbackAttachment;
    std::unique_ptr<SliderAttachment> mixAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusComponent)
};
