#define _USE_MATH_DEFINES
#include <math.h>
#include "../include/FilterAllpass.h"


FilterAllpass::FilterAllpass()
{
}


FilterAllpass::~FilterAllpass()
{
}

void FilterAllpass::calculateCoefficients(float Q, int freq, int sr)
{
    float a = (tan(M_PI * Q / sr) - 1.0 / tan(M_PI * Q / sr + 1.0));
    float b = -cos(M_PI * Q / sr);

    _coeffs.a0 = -a;
    _coeffs.a1 = b * (1.0 - a);
    _coeffs.a2 = 1.0;
    _coeffs.b1 = _coeffs.a1;
    _coeffs.b2 = _coeffs.a0;
}

float FilterAllpass::process(float in)
{
    float x = in;
    float y = _coeffs.a0 * x + _coeffs.a1 * x_1 + 
        _coeffs.a2 * x_2 - _coeffs.b1 * y_1 - _coeffs.b2 * x_2;

    x_2 = x_1;
    x_1 = x;
    y_2 = y_1;
    y_1 = y;
    
    return y;
}
