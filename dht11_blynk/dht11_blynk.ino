#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"  
#include <SimpleTimer.h>         
#define DHTTYPE DHT11
#define dht_dpin 2
DHT dht(dht_dpin, DHTTYPE); 
SimpleTimer timer;
char auth[] = "1eSL7_1ZUw4rGU5AFUp8Q4Lh5PBVnx-w";
char ssid[] = "Van Tho 15";
char pass[] = "vannhucu";
float t;
float h;
void setup()
{
    Serial.begin(9600);
   // Blynk.begin(auth, ssid, pass);
    Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 1, 13), 8080);
    dht.begin();
    timer.setInterval(2000, sendUptime);
}
void sendUptime()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  Serial.println("Humidity and temperature\n\n");
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(t); 
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V5, h);
  
}

void loop()
{
  Blynk.run();
  timer.run();
}
