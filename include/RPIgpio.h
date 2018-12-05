#ifndef RPIGPIO_H
#define RPIGPIO_H

#include <stdio.h>
#include <string>
#include <iostream>

#ifdef __arm__
#include <wiringPi.h>
#include "mcp3008Spi.h"
#endif

class RPIgpio{

public:
    RPIgpio();  // default constructor
    RPIgpio(std::vector<int> &digitalPinsOutput, std::vector<int> &digitalPinsInput);
    ~RPIgpio();
    int readAnalog3008(int pin);
    int readDigital(int pin);
    int writeDigital(int pin, int val);

private:
    std::vector<int> _digitalPinsOut;
    std::vector<int> _digitalPinsIn;
    std::vector<int> _activeAnalogPins;
    #ifdef __arm__
    mcp3008Spi *a2d;
    #endif
};

#endif
