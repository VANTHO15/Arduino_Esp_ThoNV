#include <SoftwareSerial.h>
#include "ThingSpeak.h"
#include <NTPtimeESP.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <WiFiConnector.h>
#define SECRET_CH_ID   812316    // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "Y58VDKE1MRGUI41D"   // replace XYZ with your channel write API Key
#define FIREBASE_HOST "vantho15.firebaseio.com"
#define FIREBASE_AUTH "iKUti9ZBLWlEgqYrbiIct1hHwS9fLlS6ZLHUk89H"
NTPtime NTPch("ch.pool.ntp.org");
char *ssid      = "Van Tho 15";
char *password  = "vannhucu";
strDateTime dateTime;
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
WiFiClient  client;
SoftwareSerial loraSerial(D1, D2); // TX, RX
void setup()
{
  pinMode(16, OUTPUT);
  Serial.begin(9600);
  loraSerial.begin(9600);
  Serial.println();
  Serial.println("Booted");
  Serial.println("Connecting to Wi-Fi");
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  WiFi.begin (ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/ESP8266/fan");
  Firebase.stream("/ESP8266/cho_an");
  Firebase.stream("/ESP8266/light");
}
uint16_t so, gio1, phut1, giay1;
String data, led;
void loop()
{
  dateTime = NTPch.getNTPtime(7.0, 0);
  if (dateTime.valid)
  {
    byte gio = dateTime.hour;
    byte phut = dateTime.minute;
    byte giay = dateTime.second;
    int nam = dateTime.year;
    byte thang = dateTime.month;
    byte ngay = dateTime.day;
    byte thu = dateTime.dayofWeek;
    if ((gio1 == gio) && (phut1 == phut) && (giay1 == giay))
      loraSerial.println("AN");
  }
  // thingspeak
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin (ssid, password); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
  //nhan giu lieu
  if (loraSerial.available() > 1)
  {
    String chuoi = loraSerial.readString();
    Serial.print("nhiet_do_la : ");
    Serial.println(chuoi);
    int value = chuoi.toInt();
    int x = ThingSpeak.writeField(myChannelNumber, 2, value, myWriteAPIKey);//2 la field 2
    if (x == 200)
    {
      Serial.println("Channel update successful.");
    }
    else
    {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
  }
  // firebase
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
    JsonVariant data = event.getJsonVariant("data");
    //  data.prettyPrintTo(data);
    data.printTo(Serial);
    StaticJsonBuffer<200> jsonBuffer;

    //    data.printTo(Serial);
    String hen_gio_an = data["cho_an"]["hen_gio_an"] ;
    String dc = data["fan"]["state_fan"] ;
    String led = data["light"]["state_led"];
    String hen_gio_on = data["light"]["hen_gio_on"];
    String hen_gio_off = data["light"]["hen_gio_off"];
    String giotam = hen_gio_an.substring(0, 2);
    String phuttam = hen_gio_an.substring(2, 4);
    String giaytam = hen_gio_an.substring(4, 6);
    gio1 = giotam.toInt();
    phut1 = phuttam.toInt();
    giay1 = giaytam.toInt();
    if (led == "on")
      loraSerial.println("ON");
    else if (led == "off")
      loraSerial.println("OFF");
    if (dc == "ON")
      loraSerial.println("choan");
    else if (dc == "OFF")
      loraSerial.println("dungan");
  }
}
