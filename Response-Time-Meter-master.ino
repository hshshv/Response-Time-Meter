#include "Sensors.h"
#include "RGBLed.h"
#include <Wire.h>
#include "LQ.h"

LQ lcd(0x27, 16, 2);


AnalogSensor CheckEvery(A0);
AnalogSensor RespTime(A2);

Button button(3);

Led Buzzer(7);
RGBLed Led(4, 5, 6);

void setup()
{
  RespTime.InPin = 2;
  //Wire.begin();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Ready");
  Led.TurnOn(colors::Green);
  Serial.begin(9600);

}

void loop()
{ 
    while(true)
    {
     Serial.print("Respond time input pin is: ");
     Serial.print(RespTime.InPin);
     //Serial.print(round(map(RespTime.Get(), 0, 1023, 1000, 5000)));
     //Serial.print(analogRead(A2));
     Serial.print("  | checking time input pin is:  ");
     Serial.println(CheckEvery.InPin);
     //Serial.println(map(CheckEvery.Get(), 0, 1023, 90000, 300000));
     //Serial.println(analogRead(A0));
     //Serial.println(button.Activated());
    }
  //delay(map(CheckEvery.Get(), 0, 1023, 90000, 300000));
  delay(10000);
  if (test())
  {
    Led.TurnOn(colors::Green);//Your response time is fine
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Your response");
    lcd.setCursor(0, 1);
    lcd.print("time is fine");
  }
  else
  {
    Led.TurnOn(colors::Red);//Your response time is not fine
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Your response");
    lcd.setCursor(0, 1);
    lcd.print("time isn't fine");
  }
}

bool test()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("testing respo -");
  lcd.setCursor(0, 1);
  lcd.print("press the button!");
  int respondTime = round(map(RespTime.Get(), 0, 1023, 1000, 5000));
  Buzzer.TurnOn();
  Led.TurnOn(colors::Blue);
  unsigned long Start = millis();
  while (!button.Activated() && Start + respondTime > millis())
  {
    if (Start + 750 < millis())
    {
      Buzzer.TurnOff();
    }
  }
  Buzzer.TurnOff();
  return (Start + respondTime > millis());
}
