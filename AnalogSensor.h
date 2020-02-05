#ifndef AnalogSensor_h
#define AnalogSensor_h

#include "Sensor.h"

class AnalogSensor: public Sensor
{
  public:
    AnalogSensor(int InPin, int activatedLevel);
    AnalogSensor(int InPin);
    void SetLevel(int NewLevel);
    int Get();
    bool Activated();
  private:
    byte ActivatedLevel;
};

#endif
