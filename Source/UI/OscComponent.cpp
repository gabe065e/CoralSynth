/*
  ==============================================================================

    OscComponent.cpp
    Created: 16 Sep 2024 5:39:05pm
    Author:  gabe0

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String oscId, juce::String gainId, juce::String pitchId)
{
    juce::StringArray oscChoices{ "Sine", "Saw", "Square" };
    oscSelector.addItemList(oscChoices, 1);
    oscSelector.setSelectedItemIndex(0);

    addAndMakeVisible(oscSelector);

    waveSelectorLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    waveSelectorLabel.setFont(15.0f);
    waveSelectorLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(waveSelectorLabel);



    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    gainSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    addAndMakeVisible(gainSlider);

    pitchSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    pitchSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    pitchSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::black);
    addAndMakeVisible(pitchSlider);

    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, oscId, oscSelector);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, gainId, gainSlider);

    pitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, pitchId, pitchSlider);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    gd = juce::ColourGradient(juce::Colours::coral, 0, 0, juce::Colours::black, 100, 100, false);

    //g.setGradientFill(gd);
    //g.fillAll();
}

void OscComponent::resized()
{
    const auto startY = 55;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    auto bounds = getLocalBounds();
    //oscSelector.setBounds(bounds.removeFromLeft(getWidth() / 5));
    oscSelector.setBounds(10, startY, 90, labelHeight);

    gainSlider.setBounds(120, 0, 90, bounds.getHeight() );
    pitchSlider.setBounds(200, 0, 90, bounds.getHeight());
    waveSelectorLabel.setBounds(10, startY - labelYOffset, 90, labelHeight);
}