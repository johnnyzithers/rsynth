#pragma once
#include "Delay.h"
#include "z_dsp_Utilities.h"

class Delay_Chorus : public Delay
{

    //Implementation of the vibrato effect is based on a modulated delay line, a
    //    delay line whose delay length changes over time under the control of a low -
    //    frequency oscillator(LFO), as shown in Figure2.5.Unlike other delay effects,
    //    the input signal x[n] is not mixed into the output.

public:
    Delay_Chorus(
            int length = DEFAULT_LEN_SAMPS
        , float feedback = DEFAULT_FB
        , float mix = DEFAULT_MIX
        , float freq = DEFAULT_LFO_FREQ
        , float width = DEFAULT_LFO_WIDTH
    , float sr = DEFAULT_SAMPLE_RATE);
    ~Delay_Chorus();

    void setLfoFreq(float lfoFreq);
    void setLfoWidth(float width);
    void process(float in, float* out);

private:

    float   *delayBuffer = nullptr;   // circular delay buffer
    int     _lengthSamples;           // delay size in samples
    int     _rp;                      // delay buffer read pointer
    int     _wp;

    // User-adjustable parameters:
    float _lfoFreq;     // Frequency of the LFO
    float _lfoWidth;    // Width of the LFO in samples
    float _mix;         // 0-1 wet dry mix percentagewidth
    float _feedback;    // 0-1 feedback percentage
    float _sr;

    float _ph; // REPLACE with LFO obj

};

