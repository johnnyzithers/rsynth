// Based on Synthesis/ADSRGenerator.h Created by Martin on 08.04.14.
#include <stdlib.h>
#include <iostream>

#include "../include/ADSR.h"
#include "../include/z_dsp_Utilities.h"

float ADSR::tick() {
    if (_currentStage != ADSR_STAGE_OFF && _currentStage != ADSR_STAGE_SUSTAIN) {

        if (_currentSampleIndex == _nextStageSampleIndex)
        {
            ADSRStage newStage = static_cast<ADSRStage>( (_currentStage + 1) % kNumADSRStages );
            enterStage(newStage);
        }
        _currentLevel *= _multiplier;
        _currentSampleIndex++;
    }
    return _currentLevel;
}

void ADSR::calculateMultiplier(float startLevel, float endLevel, unsigned long long lengthInSamples)
{
    _multiplier = 1.0 + (log(endLevel) - log(startLevel)) / (lengthInSamples);
}

void ADSR::enterStage(ADSRStage newStage)
{
    _currentStage = newStage;
    _currentSampleIndex = 0;

    if (_currentStage == ADSR_STAGE_OFF || _currentStage == ADSR_STAGE_SUSTAIN) {
        _nextStageSampleIndex = 0;
    } else {
        _nextStageSampleIndex = _stageValue[_currentStage] * _sr;
    }
    switch (newStage) {
        case ADSR_STAGE_OFF:
            _currentLevel = 0.0;
            _multiplier = 1.0;
            break;
        case ADSR_STAGE_ATTACK:
            _currentLevel = _minimumLevel;
            calculateMultiplier(_currentLevel,
                                1.0,
                                _nextStageSampleIndex);
            break;
        case ADSR_STAGE_DECAY:
            _currentLevel = 1.0;
            calculateMultiplier(_currentLevel,
                                fmax(_stageValue[ADSR_STAGE_SUSTAIN], _minimumLevel),
                                _nextStageSampleIndex);
            break;
        case ADSR_STAGE_SUSTAIN:
            _currentLevel = _stageValue[ADSR_STAGE_SUSTAIN];
            _multiplier = 1.0;
            break;
        case ADSR_STAGE_RELEASE:
            // We could go from ATTACK/DECAY to RELEASE, so we're not changing currentLevel here.
            calculateMultiplier(_currentLevel,
                                _minimumLevel,
                                _nextStageSampleIndex);
            break;
        default:
            break;
    }

    if (DEBUG_PRINT_ADSR) { std::cout << "entering stage: " << newStage << std::endl; }
    if (DEBUG_PRINT_ADSR) { std::cout << "_nextStageSampleIndex: " << _nextStageSampleIndex << std::endl; }
}

void ADSR::setSampleRate(float newSR) 
{
    _sr = newSR;{}
}
void ADSR::setAttack(float attackPercent)
{
	_stageValue[ADSR_STAGE_ATTACK] = attackPercent;
}
void ADSR::setDecay(float decayPercent)
{
	_stageValue[ADSR_STAGE_DECAY] = decayPercent;
}
void ADSR::setRelease(float releasePercent)
{
	_stageValue[ADSR_STAGE_RELEASE] = releasePercent;
}
void ADSR::setSustain(float sustainLevel)
{
	_stageValue[ADSR_STAGE_SUSTAIN] = sustainLevel;
}
