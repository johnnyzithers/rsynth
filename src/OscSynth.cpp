#include "../include/OscSynth.h"
#include "../include/Oscillator.h"
#include "../include/LFO.h"
#include "../include/ADSR.h"


OscSynth::OscSynth(OscWaveform waveform)
{
    // fixme - move defaults
//    _adsr.setAttackTime(20);
  //  _adsr.setDecayTime(100);
   // _adsr.setSustainTime(300);
    //_adsr.setReleaseTime(300);
    //_adsr.setSustainLevel(0.5);

    _osc.setType(OscWaveform::Cos);
    _osc.setFreq(440);

    _filt.setFc(1000.0);
    _filt.setType(0);

    _trigger = true;
    
}

OscSynth::~OscSynth()
{
}

float OscSynth::process()
{
    // default output
    float sig = 0.0f;
    
    // if a note is triggered
    if (_trigger)
    {
        // get osc sample
        sig = _osc.tick();

        // through filter
        sig = _filt.process(sig);
        
        //// if adsr has completed
        //if (sig == 99.0)
        //{
        //    // trigger off
        //    _trigger = 0;
        //}

        // through adsr
        //sig = sig * _adsr.tick();
    }
    return sig;
}

void OscSynth::changeWaveform(OscWaveform newWaveform)
{
    _osc.setType(newWaveform);
}

void OscSynth::triggerReset()
{
    _trigger = 1;
}


float OscSynth::setFreq(float newFreq)
{
    return _freq = newFreq;
}

