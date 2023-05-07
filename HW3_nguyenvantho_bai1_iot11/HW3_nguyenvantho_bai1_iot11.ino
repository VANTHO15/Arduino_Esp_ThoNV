#include <ESP8266WiFi.h>
#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif
int value=1;
const char* ssid     = "Vantho15";
const char* password = "12345678";

String host = "api.thingspeak.com";
const uint16_t port = 80;
void setup() {
  Serial.begin(115200);
  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  pinMode(0, INPUT_PULLUP);
  pinMode(16, OUTPUT);
  digitalWrite(16, 1);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println();
  }
  Serial.println();
}

void loop()
{     
     if(value==1) value=0;
     else         value=1;
     delay(15000);
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    if (!client.connect(host, port))
    {
      Serial.println("connection failed");
      delay(5000);
      return;
    }
    if (client.connected())
    {
      client.print(String ("GET ") + "/update?api_key=7C57Z6I98PI7NPXD&field1=" + String(value) + " HTTP/1.0\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    }

    unsigned long timeout = millis();
    while (client.available() == 0)
    {
      if (millis() - timeout > 5000)
      {
        Serial.println(">>> Client Timeout !");
        client.stop();
        delay(6000);
        return;
      }
    }
    // not testing 'client.connected()' since we do not need to send data here
    while (client.available())
    {
      char ch = static_cast<char>(client.read());
      Serial.print(ch);
    }
    // Close the connection
    Serial.println();
    client.stop();
    delay(1000);
}
