#include "../include/Compressor.h"
#include <math.h>


Compressor::Compressor()
{
}


Compressor::~Compressor()
{
}

void Compressor::process(float in, float * out)
{
    // level detection
    if (fabs(in) < 0.000001)
        x_g[n] = -120;
    else
        x_g[n] = 20 * log10(fabs(in));
    
    // gain computer
    if (x_g[n] >= _threshold)
        y_g[n] = _threshold + 
        (x_g[n] - _threshold) / _ratio;
    else
        y_g[n] = x_g[n];
    x_l[n] = x_g[n] - y_g[n];

    // gain smoothing
    if (x_l[0] > _yPrev)
        y_l[n] = _attackAlpha * _yPrev +
        (1 - _attackAlpha) * x_l[n];
    else
        y_l[n] = _releaseAlpha * _yPrev +
        (1 - _releaseAlpha) * x_l[n];

    // control
    c[n] = pow(10.0, (_makeupGain - y_l[n]) / 20.0);
    _yPrev = y_l[n];

    *out = in * c[n];

    // increment and wrap buffer index
    n++;
    if (n >= _bufferSize)
        n -= _bufferSize;

}

float Compressor::setThreshold(float thresh)
{
    return 0.0f;
}

float Compressor::setRatio(float rat)
{
    return 0.0f;
}

float Compressor::setAttackAlpha(float attTau)
{
    return exp(-1 / (0.001 * _sr * attTau));
}

float Compressor::setReleaseAlpha(float relTau)
{
    return exp(-1 / 0.001 * _sr * relTau);
}


float Compressor::setMakeupGain(float gain)
{
    return 0.0f;
}
