// slave
#include "mpu6050.h"
int tx, ty, tz;
void setup()
{
  Serial.begin(9600);
  mpu6050();
}
String s = "";
uint32_t tim = millis();
void loop()
{
  tx =  map(get_accx(), -16384, 16384, -90, 90);
  ty =  map(get_accy(), -16384, 16384, -90, 90);
  tz = map(get_accz(), -16384, 16384, -90, 90);
  s = s + String(tx) + "a" + String(ty) + "b" + String(tz);
  if (( millis() - tim) > 1200)
  {
    Serial.println(s);
    tim = millis();
  }
  s = "";
}
