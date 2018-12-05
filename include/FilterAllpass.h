#pragma once
#include "Filter.h"
class FilterAllpass :
    public Filter
{
public:
    FilterAllpass();
    ~FilterAllpass();

    virtual void calculateCoefficients(float Q, int freq, int sr);
    virtual float process(float in);

private:
    Coeffs _coeffs;
    float x_1, x_2, y_1, y_2;
};

