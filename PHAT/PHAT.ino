#include <SoftwareSerial.h>
#define  dco  6
#define  led  7
SoftwareSerial loraSerial(D1, D2); // TX, RX
void setup()
{
  Serial.begin(9600);
  loraSerial.begin(9600);
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
    if (input == "ON") digitalWrite(led, 0);
    if (input == "OFF") digitalWrite(led, 1);
    if(input=="choan")  digitalWrite(dco,0);
    if(input=="dungan")  digitalWrite(dco,1);
    if(input=="AN")
      {
        digitalWrite(dco,0);
        ktra=1;
        tgian=millis();
      } 
  }
  if((ktra==1)&&((millis()-tgian) >= 30000))
  {
    ktra=0;
    digitalWrite(dco,1);
  }
}
