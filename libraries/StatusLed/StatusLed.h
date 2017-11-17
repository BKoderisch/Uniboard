/**
* File describes the StatusLed library
*
* @author Benjamin Koderisch
* @verison 1.0 17.11.17
*/

#ifndef __STATUS_LED__
#define __STATUS_LED__

#include <Arduino.h>

class StatusLed {
private:
    byte statusPin;

public:
    StatusLed(byte pin);

    void setLedOn();
    void setLedOff();
    void blink(byte times, unsigned int ms);
};

#endif