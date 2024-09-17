/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 16 Sep 2024 5:36:58pm
    Author:  gabe0

  ==============================================================================
*/
#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);
    noiseAttachment = std::make_unique<SliderAttachment>(apvts, "NOISE", noiseSlider);
    driftAttachment = std::make_unique<SliderAttachment>(apvts, "DRIFT", driftSlider);

    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);

    setSliderParamsVariant(noiseSlider);
    setSliderParamsVariant(driftSlider);

    driftLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    driftLabel.setFont(15.0f);
    driftLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(driftLabel);
    noiseLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    noiseLabel.setFont(15.0f);
    noiseLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(noiseLabel);

}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint(juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::black);   // clear the background

}

void AdsrComponent::resized()
{

    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = (bounds.getWidth() - 100) / 4 - padding;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 100;
    const auto sliderStartY = 0;
    const auto labelOffset = 70;
    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);

    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    noiseSlider.setBounds(20, 30, sliderWidth - 30, sliderHeight / 3);
    driftSlider.setBounds(20, sliderHeight / 3 + 55, sliderWidth - 30, sliderHeight / 3);
    driftLabel.setBounds(30, sliderHeight / 3 + (125), sliderWidth, sliderHeight / 3);
    noiseLabel.setBounds(30, sliderHeight / 3 - 20, sliderWidth, sliderHeight / 3);


    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void AdsrComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    addAndMakeVisible(slider);

}

void AdsrComponent::setSliderParamsVariant(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 50, 25);
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    addAndMakeVisible(slider);
}

void AdsrComponent::setRotaryParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

}
