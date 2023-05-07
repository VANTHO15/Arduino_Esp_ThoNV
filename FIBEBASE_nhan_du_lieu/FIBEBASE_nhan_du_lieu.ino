#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define LedPin 16

// Set these to run example.
#define FIREBASE_HOST "vantho15.firebaseio.com"
#define FIREBASE_AUTH "iKUti9ZBLWlEgqYrbiIct1hHwS9fLlS6ZLHUk89H"
#define WIFI_SSID "Van tho 15"
#define WIFI_PASSWORD "vannhucu"

void setup() {
  pinMode(LedPin, OUTPUT);
  digitalWrite(LedPin,1);
  Serial.begin(9600);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ") ;
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/light/state");
}
void loop() {
  if (Firebase.failed()) 
  {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }

  if (Firebase.available())
  {
    FirebaseObject event = Firebase.readEvent();
    String eventType = event.getString("type");
    String path = event.getString("path");
    String data = event.getString("data");
    Serial.println(String("event: ") + eventType);
    Serial.println(String("path: ") + path);
    Serial.println(String("data: ") + data);
    if (data == "off") 
    {
      digitalWrite(LedPin, HIGH);
    } else if (data  == "on")
    {
      digitalWrite(LedPin, LOW);
    }
  }
}
