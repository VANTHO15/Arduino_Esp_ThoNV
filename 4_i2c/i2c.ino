#include     <Wire.h>
#define  DS1307 0x68
int minute,second;
void setup() {
  Wire.begin();
  Serial.begin(9600);
  DS1307_setMinute(17);
}

void loop() {
  DS1307_readMinute();
  Serial.println(minute);
  delay(1000);
}
void DS1307_setMinute(byte mnt)
{
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0x00));
  Wire.write(dectobcd(mnt));
  Wire.endTransmission();
}
void DS1307_readMinute()
{
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0x01));
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 2);
  second = bcdtodec(Wire.read()&0x7F);
  minute = bcdtodec(Wire.read());
}
int bcdtodec(byte num)
{
  return ((num / 16 * 10) + (num % 16));
}
int dectobcd(byte num)
{
  return ((num / 10 * 16) + (num % 10));
}
