#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
char auth[] = "Wug1GVP37BdgHfknRe_oDwErakFh36Gj";
char ssid[] = "Van Tho 15";
char pass[] = "vannhucu";
int n;
void setup()
{
  Serial.begin(9600);

 // Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 1, 13), 8080);
  pinMode(16,OUTPUT);
  pinMode(5,OUTPUT);
  timer.setInterval(1000L, sendUptime);
}


void sendUptime()
{
  Blynk.virtualWrite(V1, n);
}

void loop()
{
  Blynk.run();
  timer.run();
  
  n=analogRead(A0);
  Serial.println(n);
  
  if(n>500)
  {
     digitalWrite(16,LOW);
    //digitalWrite(5,HIGH);   
  }
  
  if(n<500)
  {
      digitalWrite(16,HIGH);
      //digitalWrite(5,LOW);
  }

}
