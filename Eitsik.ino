#include "Sensors.h"
#include "RGBLed.h"

AnalogSensor CheckEvery(0);
AnalogSensor RespTime(1);
Button button(3);

Led Buzzer(7);
RGBLed Led(4, 5, 6);

void setup()
{
  Led.TurnOn(colors::Green);
}

void loop()
{
  delay(map(CheckEvery.Get(), 0, 1023, 90000, 300000));
  if (test())
  {
    Led.TurnOn(colors::Green);//Your response time is fine
  }
  else
  {
    Led.TurnOn(colors::Red);//Your response time is not fine
  }
}

bool test()
{
  int respondTime = map(RespTime.Get(), 0, 1023, 1000, 5000);
  Buzzer.Blip(1000);
  Led.TurnOn(colors::Blue);
  unsigned long Start = millis();
  while (!button.Activated() || Start + respondTime > millis()) {}
  return (Start + respondTime > millis());
}
