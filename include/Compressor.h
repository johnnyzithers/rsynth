#pragma once

class Compressor
{
public:
    Compressor();
    ~Compressor();
    
    void  process(float in, float* out);
    float setThreshold(float thresh);
    float setRatio(float rat);
    float setAttackAlpha(float attTau);
    float setReleaseAlpha(float relTau);
    float setMakeupGain(float gain);

private:
    int   n;                          // buffer index 
    float *c;                       // output control voltage
    float *x_g, *x_l, *y_g, *y_l;   // control voltage calculatiom buffers
    int   _bufferSize;
    float _threshold;
    float _ratio;
    float _sr;
    float _yPrev;
    float _attackAlpha;
    float _releaseAlpha;
    float _attackTau;
    float _releaseTau;
    float _makeupGain;
};

