/**
* This file contains the functions of the AnalogTemp library
*
* @author Benjamin Koderisch
* @version 1.0 17.11.17
*/

#include "AnalogTemp.h"

// constuctor
AnalogTemp::AnalogTemp(byte pin){
    this->sensorPin = pin;
}

/**
* function read the temperature value of the sensor
*
* @return the actual temperature in Celsius
*/
int AnalogTemp::readTemp(){
    int reading = analogRead(sensorPin);
    float voltage = reading * 3.3;
    voltage /= 1024.0;
    float temperature = (voltage - 0.5) * 100;
    return temperature;
}