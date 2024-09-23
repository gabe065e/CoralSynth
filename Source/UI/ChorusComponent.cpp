/*
  ==============================================================================

    ChorusComponent.cpp
    Created: 20 Sep 2024 12:31:42pm
    Author:  gabe0

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChorusComponent.h"

//==============================================================================
ChorusComponent::ChorusComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    rateAttachment = std::make_unique<SliderAttachment>(apvts, "RATE", rateSlider);
    depthAttachment = std::make_unique<SliderAttachment>(apvts, "DEPTH", depthSlider);
    feedbackAttachment = std::make_unique<SliderAttachment>(apvts, "FEEDBACK", feedbackSlider);
    mixAttachment = std::make_unique<SliderAttachment>(apvts, "MIX", mixSlider);
    centreDelayAttachment = std::make_unique<SliderAttachment>(apvts, "CENTREDELAY", centreDelaySlider);

    
    setLabelParams(rateLabel);
    setLabelParams(mixLabel);
    setLabelParams(feedbackLabel);
    setLabelParams(depthLabel);
    setLabelParams(centreDelayLabel);

    setRotaryParams(centreDelaySlider);
    setRotaryParams(rateSlider);
    setRotaryParams(depthSlider);
    setRotaryParams(feedbackSlider);
    setRotaryParams(mixSlider);


}

ChorusComponent::~ChorusComponent()
{
}

void ChorusComponent::paint(juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::black);
}

void ChorusComponent::resized()
{

    const auto bounds = getLocalBounds().reduced(10);
    rateSlider.setBounds(10, 10, bounds.getHeight(), bounds.getHeight()-10);
    rateLabel.setBounds(10, 0, bounds.getHeight(), 15);
    depthSlider.setBounds(10 + bounds.getHeight(), 10, bounds.getHeight(), bounds.getHeight()-10);
    depthLabel.setBounds(10 + bounds.getHeight(), 0, bounds.getHeight(), 15);
    feedbackSlider.setBounds(10 + (2 * bounds.getHeight()), 10, bounds.getHeight(), bounds.getHeight()-10);
    feedbackLabel.setBounds(10 + (2 * bounds.getHeight()), 0, bounds.getHeight(), 15);
    mixSlider.setBounds(10 + (3 * bounds.getHeight()), 10, bounds.getHeight(), bounds.getHeight()-10);
    mixLabel.setBounds(10 + (3 * bounds.getHeight()), 0, bounds.getHeight(), 15);
    centreDelaySlider.setBounds(10 + (4 * bounds.getHeight()), 10, bounds.getHeight(), bounds.getHeight()-10);
    centreDelayLabel.setBounds(10 + (4 * bounds.getHeight()), 0, bounds.getHeight(), 15);




    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void ChorusComponent::setRotaryParams(juce::Slider& slider)
{

    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    addAndMakeVisible(slider);

}

void ChorusComponent::setLabelParams(juce::Label& label)
{   
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}