#include <ESP8266WiFi.h>
#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif

const char* ssid     = "TAPIT";
const char* password ="tapit168";

const char* host = "tapit.vn";
const uint16_t port = 80;
void setup() {
  Serial.begin(115200);
  // We start by connecting to a WiFi network
  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println();
  }
  Serial.println("GET / HTTP/1.0");
  Serial.println("Host: tapit.vn");
  Serial.println();
}
int a = 0;
void loop()
{
  if (a == 0)
  {
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
      client.print("GET / HTTP/1.0\r\n");
      client.print("Host: tapit.vn\r\n\r\n");
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
    a = 1;
  }
}
