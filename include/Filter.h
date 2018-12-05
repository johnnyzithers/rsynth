#pragma once
#include <stdlib.h>
#include <vector>

struct Coeffs
{
    float a0;
    float a1;
    float a2;
    float b1;
    float b2; 
};

class Filter
{
public:
    //Filter();
    virtual ~Filter() = 0;

    virtual void calculateCoefficients(float Q, int freq, int sr) = 0;
    virtual float process(float in) = 0;


private:
    Coeffs _coeffs;
    std::vector<float> x_l;
};

