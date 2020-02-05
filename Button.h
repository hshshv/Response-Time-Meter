#ifndef Button_h
#define Button_h

#include "Sensor.h"
#include "Arduino.h"

class Button: public Sensor
{
  public:
    Button(int pin);
    bool Activated();
  private:
    //int InPin;
};
#endif
