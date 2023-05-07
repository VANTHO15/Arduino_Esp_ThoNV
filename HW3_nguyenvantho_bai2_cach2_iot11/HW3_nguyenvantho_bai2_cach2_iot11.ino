#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#define SECRET_SSID "Vantho15"    // replace MySSID with your WiFi network name
#define SECRET_PASS "12345678"  // replace MyPassword with your WiFi password

#define SECRET_CH_ID  811845    // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "4IVHH6H3CN49SR1U"   // replace XYZ with your channel write API Key
char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
volatile int a = 0, value = 0;
void   ICACHE_RAM_ATTR vantho()
{
  digitalWrite(16, !digitalRead(16));
  value = !digitalRead(16);
  a = 1;
}
void setup() {
  Serial.begin(115200);  // Initialize serial
  attachInterrupt(digitalPinToInterrupt(0), vantho, FALLING);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  pinMode(0, INPUT_PULLUP);
  pinMode(16, OUTPUT);
  digitalWrite(16, 1);
}

void loop()
{
  if (a == 1)
  {
    // Connect or reconnect to WiFi
    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Attempting to connect to SSID: ");
      Serial.println(SECRET_SSID);
      while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
        Serial.print(".");
        delay(5000);
      }
      Serial.println("\nConnected.");
    }

    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeField(myChannelNumber, 2, value, myWriteAPIKey);//2 la field 2
    if (x == 200)
    {
      Serial.println("Channel update successful.");
    }
    else
    {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    a = 0;
  }
}
