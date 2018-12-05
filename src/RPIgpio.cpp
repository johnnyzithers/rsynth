#ifdef __arm__
#include <wiringPi.h>
#include <vector>
#include <algorithm>
#include "../include/RPIgpio.h"

// default constructor
RPIgpio::RPIgpio()
{
}

// default constructor
RPIgpio::RPIgpio(std::vector<int> &digitalPinsOutput, std::vector<int> &digitalPinsInput)
{
    // mcp setup
    a2d = new mcp3008Spi("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
    //wiringPi setup
    wiringPiSetup();

    // set output pins
    for (unsigned int i = 0; i < digitalPinsOutput.size(); i++){
        #ifdef __arm__
        pinMode (digitalPinsOutput[i], OUTPUT);
        #endif
    }
    // set input pins
    for (unsigned int j = 0; j < digitalPinsInput.size(); j++){
        #ifdef __arm__
        pinMode (digitalPinsInput[j], INPUT);
        #endif
    }
}

// read digital pin / BUTTON
int RPIgpio::readDigital(int pin)
{
	if(std::find(_digitalPinsIn.begin(), _digitalPinsIn.end(), pin) != _digitalPinsIn.end())
	{
		// channel is in input list
		return digitalRead(pin);
	}
	else
	{
		// channel not in input list 
		// FIXME provide error
		return -1;
	}
}

// write digital pin / LED
int RPIgpio::writeDigital(int pin, int val)
{
	if(std::find( _digitalPinsOut.begin(), _digitalPinsOut.end(), pin) != _digitalPinsOut.end())
	{
		// channel is in output list
		digitalWrite(pin, val);
		return 1;
	}
	else
	{
		// channel not in output list
		// FIXME provide error
		return -1;
	}
}

//read mcp3008 channel
int RPIgpio::readAnalog3008(int channel)
{

	if(std::find( _activeAnalogPins.begin(), _activeAnalogPins.end(), channel) != _activeAnalogPins.end())
	{
	    int val = 0;
	    unsigned char data[3];

	    data[0] = 1;                                    // first byte transmitted -> start bit
	    data[1] = 0b10000000 |( ((channel & 7) << 4));  // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
	    data[2] = 0;                                    // third byte transmitted....don't care

	    a2d->spiWriteRead(data, sizeof(data) );

	    val = 0;
	    val = (data[1]<< 8) & 0b1100000000;          	// merge data[1] & data[2] to get result
	    val |= (data[2] & 0xff);

	    return val;
	}
	else
	{
		return -1;
	}
}

#endif
