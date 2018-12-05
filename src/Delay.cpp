#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>

#include "../include/Delay.h"


Delay::Delay(int length
    , float feedback
    , float mix
    , float sr)
    : _lengthSamples(length)
    , _feedback(feedback)
    , _mix(mix)
    , _sr(sr)
{
    delayBuffer = (float*)calloc(MAX_DELAY_LEN, sizeof(float));
}

Delay::~Delay()
{
    delete delayBuffer;
    delayBuffer = nullptr;  // need both?
}

int Delay::setDelayLength(int len)
{
    return std::max(0, std::min(_lengthSamples, MAX_DELAY_LEN));
}

float Delay::setFeedback(float fb)
{
    return std::max(0.0f, std::min(_feedback, 1.0f));
}

float Delay::setMix(float mix)
{
    return std::max(0.0f, std::min(_mix, 1.0f));
}

void Delay::process(float in, float* out)
{
    // first capture output sample
    *out = _mix * in + (1.f - _mix) * delayBuffer[_rp];
    
    // write to delay buffer, with feedback
    delayBuffer[_wp] = in + (delayBuffer[_rp] * _feedback);

    // incrememnt and wrap pointers
    if (_wp >= _lengthSamples)
        _wp = 0;
    if (_rp >= _lengthSamples)
        _rp = 0;
}
