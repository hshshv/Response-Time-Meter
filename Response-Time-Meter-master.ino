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
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Ready");
  Led.TurnOn(colors::Green);
  Serial.begin(9600);
  while(true)
  {/*
    Serial.print("Check every: ");
    Serial.print(GetDelayTime());
    Serial.print("  | Resp time: ");
    Serial.println(GetRespTime());*/
    Serial.print("Check every: ");
    Serial.print(CheckEvery.Get());
    Serial.print("  | Resp time: ");
    Serial.println(analogRead(A1));
  }
}

int respondTime;
int yourTime;
void loop()
{
  delay(GetDelayTime());
  //delay(10000);

  yourTime = test();

  if (yourTime < respondTime)
  {
    Led.TurnOn(colors::Green);//Your response time is fine
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("time: ");
    lcd.setCursor(6, 0);
    lcd.print(yourTime);
    lcd.setCursor(7 + IntsDigits(yourTime), 0);
    lcd.print("ms");
    lcd.setCursor(0, 1);
    lcd.print("this is fine");
  }
  else
  {
    Led.TurnOn(colors::Red);//Your response time is not fine
    Led.TurnOff();
    Led.TurnOn(colors::Red);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("time exceeded");
    lcd.setCursor(0, 1);
    lcd.print("this is not fine");
  }
}

int test()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("testing respo -");
  lcd.setCursor(0, 1);
  lcd.print("press the button!");
  respondTime = GetRespTime();
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
  return (millis() - Start);
}

int IntsDigits(int theInt)
{
  theInt = abs(theInt);
  if (theInt < 100000 && theInt >= 10000)
  {
    return (5);
  }
  if (theInt < 10000 && theInt >= 1000)
  {
    return (4);
  }
  if (theInt < 1000 && theInt >= 100)
  {
    return (3);
  }
  if (theInt < 100 && theInt >= 10)
  {
    return (2);
  }
  if (theInt < 10)
  {
    return (1);
  }
}

int GetDelayTime()//כל כמה זמן לבצע בדיקה?
{
  return(map(CheckEvery.Get(), 0, 1023, 5000, 1800000));
}

int GetRespTime()
{
  return(round(map(RespTime.Get(), 0, 1023, 1000, 5000)));
}
