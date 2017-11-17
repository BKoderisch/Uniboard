/**
* File describe the functions of the StatusLed library
*
* @author Benjamin Koderisch
* @version 1.0 17.11.17
*/
#include "StatusLed.h"

// constuctor
StatusLed::StatusLed(byte pin){
    this->statusPin = pin;
}

/**
* function to turn the status led on
*/
void StatusLed::setLedOn(){
    analogWrite(statusPin, 255);
}

/**
* function to turn the status led off
*/
void StatusLed::setLedOff(){
    analogWrite(statusPin, 0);
}

/**
* function to create a blink effect
*
* @param times describes how often the led will blink
* @param ms duration between two blinks
*/
void StatusLed::blink(byte times, unsigned int ms){
    for(byte i = 0; i < times; i++){
        setLedOn();
        delay(ms);
        setLedOff();
        delay(ms);
    }
}