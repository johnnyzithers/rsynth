#pragma once
#include "z_dsp_Utilities.h"
class Delay
{
public:
    Delay(
            int length = DEFAULT_LEN_SAMPS
        , float feedback = DEFAULT_FB
        , float mix = DEFAULT_MIX
        , float sr = DEFAULT_SAMPLE_RATE);
    ~Delay();

    int setDelayLength(int len);
    float setFeedback(float fb);
    float setMix(float mix);
    virtual void process(float in, float *out);
    virtual int getSampleRate() { return _sr; };

private:
    float   *delayBuffer = nullptr;   // circular delay buffer
    int     _rp;                      // delay buffer read pointer
    int     _wp;                      // delay buffer write pointer

    // user controllable parameters:
    int     _lengthSamples;           // delay size in samples
    float   _feedback;                // 0-1 feedback percentage
    float   _mix;                     // 0-1 wet dry mix percentage
    int     _sr;

};

