
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "14093e7f4a0942d5a7e5556c4d775e5f";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "TAPIT";
char pass[] = "tapit168";

void setup()
{
  // Debug console
  Serial.begin(9600);
 pinMode(0,INPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}
int x=0,tho=0;
void loop()
{
  int data=digitalRead(0);
  if(data==0)    tho=1;
  if(tho==1)
  x=!x;
  if(x==0) Blynk.virtualWrite(16, 1);
  else        Blynk.virtualWrite(16, 0);
  Blynk.run();
  tho=0;
}
