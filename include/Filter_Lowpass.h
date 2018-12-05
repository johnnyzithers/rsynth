#pragma once
#include "Filter.h"
#include "z_dsp_Utilities.h"

class Filter_Lowpass :
    public Filter
{
public:
    Filter_Lowpass(
          int sr = DEFAULT_SAMPLE_RATE
        , float cuttoffFreq = DEFAULT_LP_FREQ
        , float peakGainDB = DEFAULT_GAIN_DB);
    ~Filter_Lowpass();

    virtual void calculateCoefficients(float Q, int freq, int sr);
    virtual float process(float in);

private:
    Coeffs _coeffs;
    float _sr;
    float _freq;
    float _q;
    float _peakGainDB;
    float x_1, x_2, y_1, y_2;
};

