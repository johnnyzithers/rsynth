#pragma once
#include "LFO.h"

class Tremolo
{
public:
    Tremolo(
           float sr = DEFAULT_SAMPLE_RATE
        , float lfoFreq = DEFAULT_LFO_FREQ
        , float lfoDepth = DEFAULT_LFO_WIDTH
        , LfoType lfoType = LfoType::lfoCos);
    ~Tremolo();

    void process(float in, float* out);
    void setLfoType(LfoType newType);

private:
    LFO *_tremoloLFO;
};

