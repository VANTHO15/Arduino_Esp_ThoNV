#include <SoftwareSerial.h>
#define  dco  10
#define  led  9
SoftwareSerial loraSerial(D1, D2); // TX, RX
void setup()
{
  Serial.begin(115200);
  loraSerial.begin(115200);
  pinMode(dco, OUTPUT);
  pinMode(led, OUTPUT);
}
float ndo;
uint8_t data,ktra=0;
unsigned long long tgian;
void loop()
{
  data = analogRead(A0);
  ndo = (data * 330) / 1023.0;
  loraSerial.print(String(ndo));
  if (loraSerial.available() > 1)
  {
    String input = loraSerial.readString();
    if (input == "ON") digitalWrite(led, 1);
    if (input == "OFF") digitalWrite(led, 0);
    if(input=="choan")  digitalWrite(dco,1);
    if(input=="dungan")  digitalWrite(dco,0);
    if(input=="AN")
      {
        digitalWrite(dco,1);
        ktra=1;
        tgian=millis();
      } 
  }
  if((ktra==1)&&((millis()-tgian) >= 30000))
  {
    ktra=0;
    digitalWrite(dco,0);
  }
   Serial.println("Van THo 15");
}
