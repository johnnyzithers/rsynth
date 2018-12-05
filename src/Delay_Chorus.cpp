#define _USE_MATH_DEFINES
#include <math.h>

#include <stdlib.h>
#include <algorithm>
#include "../include/Delay_Chorus.h"
#include "../include/z_dsp_Utilities.h"


Delay_Chorus::Delay_Chorus(int length
    , float feedback
    , float mix
    , float freq
    , float width
    , float sr)
    : _lengthSamples(length)
    , _feedback(feedback)
    , _mix(mix)
    , _lfoFreq(freq)
    , _lfoWidth(width)
    , _sr(sr)
{
    delayBuffer = (float*)calloc(MAX_DELAY_LEN_CHORUS, sizeof(float));

}


Delay_Chorus::~Delay_Chorus()
{
}

void Delay_Chorus::process(float in, float* out)
{
    float interpSamp = 0.0f;

    // calculate current delay *** replace with LFO obj
    // scale halfwave rectified sin
    float currDelay = _lfoWidth * (0.5f + (0.5f * sin(2.0 * M_PI * _ph)));

    // compute rp for 3 sample interpolation 
    _rp = fmodf(float(_wp) - float(currDelay * getSampleRate()) + float(_lengthSamples) - 3.0, float(_lengthSamples));

    // linear interp
    float frac = _rp - floorf(_rp);
    int prevSamp = int(floorf(_rp));
    int nextSamp = (prevSamp + 1) % _lengthSamples;    
    interpSamp = frac * delayBuffer[nextSamp] + (1.0f - frac)*delayBuffer[prevSamp];

    // write dry input to delaybuffer
    delayBuffer[_wp] = in;

    // Increment the write pointer at a constant rate
    if (++_wp >= _lengthSamples)
        _wp = 0;

    // write delayed and interpolated data to output
    *out = interpSamp;

    // update lfo phase
    _ph += _lfoFreq * (1 / getSampleRate());


}

void Delay_Chorus::setLfoFreq(float lfoFreq)
{
}

// sets the width in samples
void Delay_Chorus::setLfoWidth(float width)
{
    
}
