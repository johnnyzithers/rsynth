#define _USE_MATH_DEFINES
#include <math.h>
#include "../include/RMSAnalyzer.h"


RMSAnalyzer::RMSAnalyzer(
	  int sr
	, int frameSize)
	: _sr(sr),
	_frameSize(frameSize)
{
}

RMSAnalyzer::~RMSAnalyzer()
{
}

float RMSAnalyzer::analyze(float * inBuf)
{
    float sum = 0.0f;

    for (int i = 0; i < _frameSize; i++)
    {
        sum += inBuf[i];
    }

    return sqrt(sum / _frameSize);
}

void RMSAnalyzer::setFrameSize(int size)
{
    _frameSize = size;
}

float RMSAnalyzer::getRms()
{
    return _rms;
}
