#include "AnalogSensor.h"

AnalogSensor::AnalogSensor(int inPin, int activatedLevel)
{
  SetInPin(inPin);
  ActivatedLevel = activatedLevel;
  pinMode(InPin, INPUT);
}

AnalogSensor::AnalogSensor(int inPin)
{
  AnalogSensor(inPin, 512);
}

void AnalogSensor::SetLevel(int NewLevel)
{
  ActivatedLevel = NewLevel;
}
    
int AnalogSensor::Get()
{
  return (analogRead(InPin));
}

bool AnalogSensor::Activated()
{
  return (Get() >= ActivatedLevel);
}
