#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include "EBYTE.h"
const char *ssid = "Van Tho 15";
const char *password = "vannhucu";
struct DATA {
  unsigned long Count;
  int Bits;
  float Volts;
  float Amps;
};
int Chan;
DATA MyData;
SoftwareSerial ESerial(1, 3);
EBYTE Transceiver(&ESerial, 4, 5, 9);
void setup_wifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
void setup() {

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, INPUT);

  Serial.begin(9600);

  ESerial.begin(9600);
  Serial.println("Starting Reader");

  Transceiver.init();
  // Transceiver.Reset();
  // Transceiver.SetAirDataRate(ADR_8K);
  //Transceiver.SetAddressH(0);
  //Transceiver.SetAddressL(0);
  //Transceiver.SetChannel(2);

  // Transceiver.SaveParameters(PERMANENT);

  Transceiver.PrintParameters();
  setup_wifi();
}

void loop() {

  if (ESerial.available()) {

    Transceiver.GetStruct(&MyData, sizeof(MyData));

    Serial.print("Count: "); Serial.println(MyData.Count);
    Serial.print("Bits: "); Serial.println(MyData.Bits);
    Serial.print("Volts: "); Serial.println(MyData.Volts);
  }
  else {
    if (Serial.available()) {
      Chan = Serial.read();

      if (Chan > 47) {
        Serial.println(Chan - 48);
        Transceiver.SetChannel(Chan - 48);
        Transceiver.SaveParameters(PERMANENT);
        Transceiver.PrintParameters();
      }
    }
    delay(1000);
    Serial.println("Searching: ");
  }
}
