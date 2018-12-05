#pragma once
#ifndef FilterBiquad_h
#define FilterBiquad_h

#include "Filter.h"

enum eqType {
    lowpass = 0,
    highpass,
    bandpass,
    notch,
    peak,
    lowshelf,
    highshelf
};

class FilterBiquad 
{
public:
    
    FilterBiquad();
    FilterBiquad(int type, float Fc, float Q, float peakGainDB);
    ~FilterBiquad();
    
    void setType(int type);
    void setQ(float Q);
    void setFc(float Fc);
    void setPeakGain(float peakGainDB);
    void setBiquad(int type, float Fc, float Q, float peakGain);
    float process(float in);

protected:
    void calcBiquad(void);

    int type;
    float a0, a1, a2, b1, b2;
    float Fc, Q, peakGain;
    float z1, z2;
};

inline float FilterBiquad::process(float in) {
    float out = in * a0 + z1;
    z1 = in * a1 + z2 - b1 * out;
    z2 = in * a2 - b2 * out;
    return out;
}

#endif // Filter_Biquad.h