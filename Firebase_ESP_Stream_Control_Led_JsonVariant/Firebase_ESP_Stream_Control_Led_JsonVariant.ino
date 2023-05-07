#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define LedPin 16

// Set these to run example.
#define FIREBASE_HOST "esp8266light.firebaseio.com"
#define FIREBASE_AUTH "qRC0A4LpFBc4tWiulxijSQPwqqrvgetlBLWEHCMU"
#define WIFI_SSID "IoT-Research"
#define WIFI_PASSWORD "Tapit168"

void setup() {
  pinMode(LedPin, OUTPUT);
  Serial.begin(115200);
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
  Firebase.stream("/ESP8266");
}
void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }

  if (Firebase.available()) {
    FirebaseObject event = Firebase.readEvent();
    String eventType = event.getString("type");
    String path = event.getString("path");
    String data;
    Serial.println(String("event: ") + eventType);
    Serial.println(String("path: ") + path);
    JsonVariant jsonVariant = event.getJsonVariant("data");
    jsonVariant.prettyPrintTo(data);
    Serial.println(String("data: ") + data);
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(data);
    if (!root.success()) {
      Serial.println(F("Parsing failed!"));
      return;
    }
    if (path == "/light") {
      String state = root["state"];
      Serial.println(String("state: ") + state);
      if (state == "on") {
        digitalWrite(LedPin, LOW);
      }
      else if (state == "off") {
        digitalWrite(LedPin, HIGH);
      }
    }
  }
}
