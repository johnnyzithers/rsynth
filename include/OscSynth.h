#pragma once
#include "Oscillator.h"
#include "LFO.h"
#include "ADSR.h"
#include "FilterBiquad.h"

class OscSynth
{
public:
    OscSynth(OscWaveform waveform);
    ~OscSynth();

    float process();
    float setFreq(float newFreq);
    void changeWaveform(OscWaveform newWaveform);

    void triggerReset();

private:
    ADSR            _adsr;
    Oscillator      _osc;
    LFO             _lfo;
    FilterBiquad    _filt;
    
    bool            _trigger;
    bool            _subFlag;
    float           _freq;
};

