#include "../include/Sequencer.h"
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "../include/z_dsp_Utilities.h"

using namespace std;

Sequencer::Sequencer(
      int sr
    , int len
    , float bpm
    , int stepIndex
    , int rp)
    : _sr(sr)
    , _numSteps(len)
    , _bpm(bpm)
    , _stepIndex(0)
    , _rp(0)
{
    srand (time(NULL));

    _attackPercent  = 0.1f;
    _decayPercent   = 0.1f;
    _releasePercent = 0.4f;
}

Sequencer::~Sequencer()
{
}

float Sequencer::tick()
{
    float val = 0.0f;

    // sustain happens here
    if (_adsr.getCurrentStage() == ADSR::ADSR_STAGE_SUSTAIN) 
    {
        _adsr.enterStage(ADSR::ADSR_STAGE_RELEASE);
        // FIXME instead of entering release immediately.. start sustain timing
    }

    // if sustain timing is over, enter release
    val = _adsr.tick() * _pattern[_stepIndex];

    // wrap step pointer
    if (_rp++ >= _stepSamples)
    {
        _stepIndex++;
        _rp = 0;
        _adsr.enterStage(ADSR::ADSR_STAGE_ATTACK);
    }

    // wrap _stepIndex
    if (_stepIndex >= _numSteps)
    {

	    _stepIndex = 0;
    }

    return val;
}

std::vector<float> Sequencer::loadPattern()
{
    return std::vector<float>();
}

std::vector<float> Sequencer::randomPattern()
{
    _pattern.clear();

    for (int i = 0; i < _numSteps; i++)
    {
        _pattern.push_back(random());
    }
    return _pattern;
}

std::vector<float> Sequencer::getCurrentPattern()
{
    return _pattern;
}

int Sequencer::setSeqLength(int newSeqSize)
{
    return _numSteps = newSeqSize;
}

float Sequencer::setTempo(float newTempo)
{
    float lastTempo = _bpm;
    _bpm = newTempo;
    float tempoRatio = newTempo/lastTempo;
    // compute size of step
    _stepSamples = int(_sr / (_bpm / 60.0f));

    cout << "!!!!!" << _stepSamples << endl;

    // scale the adsr percents
    // FIXME need to add ratioReduce methods to ADSR class
    _adsr.setAttack ((tempoRatio * _attackPercent) * 0.8f);
    _adsr.setDecay ((tempoRatio * _decayPercent) * 0.9f);
    _adsr.setRelease ((tempoRatio * _releasePercent) * 0.9f);

    return _bpm;
}

float Sequencer::random()
{
    if (rand() % 2 == 0) {
        return 1.0f;
    } else {

    } return 0.0f;
}

int Sequencer::setSampleRate(int newSR)
{
    _adsr.setSampleRate(newSR);
    return _sr = newSR;
}

