#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "14093e7f4a0942d5a7e5556c4d775e5f";
char ssid[] = "Vantho15";
char pass[] = "12345678";
volatile int a = 0;
void   ICACHE_RAM_ATTR vantho()
{
  long i;
  for ( i = 0; i <= 50000; i++);
  while ((digitalRead(0) == 0) && (i < 100000))
    i++;
  for ( i = 0; i <= 50000; i++);
  a++;
  if (a % 2 == 0)
  {
    Blynk.virtualWrite(16, 0);
    digitalWrite(16, 1);
  }
  else
  {
    Blynk.virtualWrite(16, 1);
    digitalWrite(16, 0);
  }
}
BLYNK_WRITE(16)
{
  int value = param.asInt();
  if (value == 1)
  {
    digitalWrite(16, 0);
    a = 0;
  }
  else
  {
    digitalWrite(16, 1);
    a = 1;
  }
}
WidgetLCD lcd(0);
void  hienthi()
{
  lcd.clear();
  int y=analogRead(A0);
  float ndo=(y*330)/1023.0;
  lcd.print(4,0,ndo);
  lcd.print(9,0," do c");
}
void setup()
{
  Serial.begin(115200);
  pinMode(0, INPUT);
  pinMode(16, OUTPUT);
  pinMode(A0, OUTPUT);
  digitalWrite(16, 1);
  Blynk.begin(auth, ssid, pass);
  attachInterrupt(digitalPinToInterrupt(0), vantho, FALLING);
  lcd.clear();
  hienthi();
}
  long tg=millis();
void loop()
{
  if(millis()-tg==5000) 
  {
    hienthi();
    tg=0;
  }
  Blynk.run();
}
BLYNK_CONNECTED()
{
  Blynk.syncVirtual(16);
}
