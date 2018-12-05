#pragma once
#include "z_dsp_Utilities.h"


class RMSAnalyzer
{
public:
    RMSAnalyzer(int sr = DEFAULT_SAMPLE_RATE
	, int frameSize = DEFAULT_FRAME_SIZE);
    ~RMSAnalyzer();

    float analyze(float *frameIn);
    void setFrameSize(int size);
    float getRms();

private:

    int _sr;
    int _frameSize;
    float _rms;

};

