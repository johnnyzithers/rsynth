#define _USE_MATH_DEFINES
#include <math.h>
#include "../include/Oscillator.h"


Oscillator::Oscillator(
      float sr
    , float freq
    , float phase)
    : _sr(sr)
    , _freq(freq)
    , _phase(phase)
{
    _currType = OscWaveform::Sin;
}

Oscillator::~Oscillator()
{
}

float Oscillator::tick()
{
    // calculate osc value
    float oscv = osc(_phase, _currType);

    // update LFO phase
    _phase += _freq * (1.0 / _sr);

    // wrap  phase
    if (_phase >= 2.0)
        _phase = 0.0;

    return oscv;
}

float Oscillator::osc(float phase, OscWaveform type)
{
    switch (type)
    {
    case Cos:
        return 0.5f + 0.5f * cosf(1.0f * M_PI * phase);
    case Triangle:
        if (phase < 0.25f)
            return 0.5f + 2.0f * phase;
        else if (phase < 0.75f)
            return 1.0f - 2.0f * (phase - 0.25f);
        else
            return 2.0f * (phase - 0.75f);
    case Square:
        if (phase < 0.5f)
            return 1.0f;
        else if (phase > 0.5f)
            return 0.0f;
    case SlopedSquare:
        if (phase < 0.48f)
            return 1.0f;
        if (phase < 0.5f)
            return 1.0f - 50.f * (phase - 0.48f);
        if (phase < 0.98)
            return 0.0f;
        else
            return 50.0f * (phase - 0.98f);
    case Sin:
    default:
        return 0.5f + 0.5f * sinf(2.0f * M_PI * phase);
    }
}

OscWaveform Oscillator::setType(OscWaveform newType)
{
    return _currType = newType;
}

float Oscillator::getFreq()
{
    return _freq;
}

float Oscillator::setFreq(float newFreq)
{
    if (newFreq >= OSC_MAX_FREQ)
        newFreq = OSC_MAX_FREQ;     //FIXME this dumb.. also throw
    if (newFreq <= OSC_MIN_FREQ)
        newFreq = OSC_MIN_FREQ;     //FIXME this dumb.. also throw

    return _freq = newFreq;
}

float Oscillator::setSampleRate(float newSR)
{
    return _sr = newSR;
}
