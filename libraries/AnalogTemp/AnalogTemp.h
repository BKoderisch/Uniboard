/**
* This file describes the AnalogTemp library.
*
* @author Benjamin Koderisch
* @version 1.0 17.11.17
*/

#ifndef __ANALOG_TEMP__
#define __ANALOG_TEMP__

#include <Arduino.h>

class AnalogTemp{
private:
    byte sensorPin;

public:
    AnalogTemp(byte pin);

    int readTemp();
};

#endif