#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"

class Sensor
{
  public:
    int InPin;
    /*
      Sensor(byte pin);
    */
    bool Activated();
    void SetInPin(int newPin);
    };
#endif
