#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "vantho15.firebaseio.com"
#define FIREBASE_AUTH "iKUti9ZBLWlEgqYrbiIct1hHwS9fLlS6ZLHUk89H"
#define WIFI_SSID "TAPIT"
#define WIFI_PASSWORD "tapit168"

void setup() {
  Serial.begin(115200);
  pinMode(16, OUTPUT);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/esp8266/light/state");
}
void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }
  if (Firebase.available())
  {
    FirebaseObject event = Firebase.readEvent();
    String eventType = event.getString("type");
    eventType.toLowerCase();
    if (eventType == "put")
    {
      String data = event.getString("/esp8266/light/state");
      if (data == "ON")  digitalWrite(16, 0);
      else if (data == "OFF")   digitalWrite(16, 1);

    }
  }

}
