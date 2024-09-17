/*
  ==============================================================================

    AdsrData.cpp
    Created: 16 Sep 2024 5:38:36pm
    Author:  gabe0

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::update(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

    setParameters(adsrParams);
}