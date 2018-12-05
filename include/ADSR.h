//  ADSR.h - based on - Synthesis/EnvelopeGenerator.h  -Created by Martin on 08.04.14.

#ifndef __ADSR__
#define __ADSR__

#include <cmath>

class ADSR {
public:
    enum ADSRStage {
        ADSR_STAGE_OFF = 0,
        ADSR_STAGE_ATTACK,
        ADSR_STAGE_DECAY,
        ADSR_STAGE_SUSTAIN,
        ADSR_STAGE_RELEASE,
        kNumADSRStages
    };

    void enterStage(ADSRStage newStage);
    float tick();
    void setAttack(float attackPercent);
    void setDecay(float decayPercent);
    void setRelease(float releasePercent);
    void setSustain(float sustainLevel);
    void setSampleRate(float newSR);
    inline ADSRStage getCurrentStage() const { return _currentStage; };
    const float _minimumLevel;
    
    ADSR() :
    _minimumLevel(0.00000000000001f),
    _currentStage(ADSR_STAGE_OFF),
    _currentLevel(_minimumLevel),
    _multiplier(1.0),
    _sr(44100.0),
    _currentSampleIndex(0),
    _nextStageSampleIndex(0) {
        _stageValue[ADSR_STAGE_OFF]     = 0.0;
        _stageValue[ADSR_STAGE_ATTACK]  = 0.1;
        _stageValue[ADSR_STAGE_DECAY]   = 0.5;
        _stageValue[ADSR_STAGE_SUSTAIN] = 0.1;
        _stageValue[ADSR_STAGE_RELEASE] = 1.0;
    };
private:
    ADSRStage           _currentStage;
    float               _currentLevel;
    float               _multiplier;
    float               _sr;
    float               _stageValue[kNumADSRStages];
    unsigned long long  _currentSampleIndex;
    unsigned long long  _nextStageSampleIndex;
    void calculateMultiplier(float startLevel, float endLevel, unsigned long long lengthInSamples);

};

#endif 


/* defined(__ADSR__) */
