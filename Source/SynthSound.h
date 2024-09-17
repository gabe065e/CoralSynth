/*
  ==============================================================================

    SynthSound.h
    Created: 16 Sep 2024 4:45:53pm
    Author:  gabe0

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class synthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};
