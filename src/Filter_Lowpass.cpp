#include "../include/Filter_Lowpass.h"
#define _USE_MATH_DEFINES
#include <math.h>


Filter_Lowpass::Filter_Lowpass(
    int sr
    , float cuttoffFreq
    , float peakGainDB)
    : _sr(sr)
    , _freq(cuttoffFreq)
    , _peakGainDB(peakGainDB)
{
}

Filter_Lowpass::~Filter_Lowpass()
{
}

void Filter_Lowpass::calculateCoefficients(float Q, int freq, int sr)
{
//    double v = pow(10.0, fabs(_peakGainDB) / 20.0);
    double k = tan(M_PI * _freq);
    double norm = 1 / (1 + k / _q + k * k);
    _coeffs.a0 = k * k * norm;
    _coeffs.a1 = 2.0 * _coeffs.a0;
    _coeffs.a2 = _coeffs.a0;
    _coeffs.b1 = 2 * (k * k - 1) * norm;
    _coeffs.b2 = (1 - k / _q + k * k * norm);
}

float Filter_Lowpass::process(float in)
{
    float x = in;
    float y = _coeffs.a0 * x + _coeffs.a1 * x_1 +
        _coeffs.a2 * x_2 - _coeffs.b1 * y_1 - _coeffs.b2 * x_2;

    x_2 = x_1;
    x_1 = x;
    y_2 = y_1;
    y_1 = y;

    return y;
}
