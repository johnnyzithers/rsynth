#include "../include/Tremolo.h"

Tremolo::Tremolo(
      float sr
    , float lfoFreq
    , float lfoDepth
    , LfoType lfoType)
{
    _tremoloLFO = new LFO(sr, lfoFreq, lfoDepth, lfoType);
}

Tremolo::~Tremolo()
{
    delete _tremoloLFO;
    _tremoloLFO = nullptr;
}

void Tremolo::process(float in, float * out)
{
    float lfoVal = _tremoloLFO->tick();
    *out = in * (1.0f - _tremoloLFO->getDepth() * lfoVal);
}

void Tremolo::setLfoType(LfoType newType)
{
    _tremoloLFO->setType(newType);
}
