#include "DigitalSensor.h"

DigitalSensor::DigitalSensor(int inPin)
{
  InPin = inPin;
  pinMode(InPin, INPUT);
}

bool DigitalSensor::Activated()
{
  return (digitalRead(InPin));
}
