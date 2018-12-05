#pragma once
#include <vector>
#include "z_dsp_Utilities.h"
#include "ADSR.h"

class Sequencer
{
public:
    Sequencer(
          int sr = DEFAULT_SAMPLE_RATE
        , int len = DEFAULT_SEQUENCER_LENGTH
        , float bpm = DEFAULT_BPM
	, int stepIndex = 0
	, int rp = 0);
    ~Sequencer();

    float tick();
    std::vector<float> loadPattern();
    std::vector<float> randomPattern();
    std::vector<float> getCurrentPattern();
    int setSeqLength(int newSeqLen);
    int setSampleRate(int newSR);
    float setTempo(float newTempo);
    float random();

    ADSR                _adsr;

private:
    std::vector<float>  _pattern;
    float               _attackPercent;
    float               _decayPercent;
    float               _releasePercent;
    int                 _sr;
    int                 _numSteps;
    float               _bpm;
    int                 _stepIndex;
    int                 _rp;
    int                 _stepSamples;
    int                 _patternSamples;
};

