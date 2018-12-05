#pragma once
#include "z_dsp_Utilities.h"

enum OscWaveform {
    Sin, 
    Cos, 
    Triangle,
    Square,
    SlopedSquare
};

 class Oscillator
{
public:
    Oscillator(
           float sr = DEFAULT_SAMPLE_RATE
        , float freq = DEFAULT_OSC_FREQ
        , float phase = 0.0f);
    ~Oscillator();

    float tick();
    float osc(float phase, OscWaveform type);
    OscWaveform setType(OscWaveform newType);
    float setFreq(float newFreq);
    float getFreq();
    float setSampleRate(float newSR);

private:
    OscWaveform _currType;
    float       _sr;
    float       _freq;
    float       _phase;
};

