#include <Wire.h>

#define DS1307 0x68

volatile int second, minute, hour, day, date, month, year;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  DS1307_SetTime(23, 58, 00, 25, 6, 18, 6);
  DS1307_ReadTime();
  Serial.println("FINISH SET TIME");
  DS1307_SetSQWPin1Hz();
}

void loop() {
  DS1307_ReadTime();
  Serial.print(hour); Serial.print(":");Serial.print(minute); Serial.print(":"); Serial.println(second);
  delay(100);
}


void DS1307_ReadTime()
{
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0x00));
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);

  second = bcdtodec(Wire.read() & 0x7f);
  minute = bcdtodec(Wire.read());
  hour   = bcdtodec(Wire.read() & 0x3f);
  day    = bcdtodec(Wire.read());
  date   = bcdtodec(Wire.read());
  month  = bcdtodec(Wire.read());
  year   = bcdtodec(Wire.read());
}

int bcdtodec(byte num)      //chuy?n d?i t? h? 16bit sang h? 10bit  //Ð? d?c th?i gian
{
  return ((num / 16 * 10) + (num % 16));
}

int dectobcd(byte num)      //chuy?n d?i t? h? 10bit sáng h? 16bit  // Ð? cài d?t th?i gian
{
  return ((num / 10 * 16) + (num % 10));
}

void DS1307_SetTime(byte hr, byte mnt, byte sec, byte dt, byte mth, byte y, byte d)
{
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0x00));
  Wire.write(dectobcd(sec));
  Wire.write(dectobcd(mnt));
  Wire.write(dectobcd(hr));
  Wire.write(dectobcd(d));
  Wire.write(dectobcd(dt));
  Wire.write(dectobcd(mth));
  Wire.write(dectobcd(y));
  Wire.endTransmission();
}

void DS1307_SetSQWPin1Hz()
{
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0x07));
  Wire.write(byte(0x10));
  Wire.endTransmission();
}
