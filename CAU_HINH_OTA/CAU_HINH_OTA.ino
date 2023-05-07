#include <SoftwareSerial.h>
SoftwareSerial HC05(2,3); // tx rx
void setup()
{
Serial.begin(9600);
Serial.println("Enter AT commands:");
HC05.begin(38400);
}
void loop()
{
  if (HC05.available())
    Serial.write(HC05.read());
  if (Serial.available())
    HC05.write(Serial.read());
}
