
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#ifndef APSSID
#define  APSSID "Vantho15"
#define  APPSK "12345678"
#endif    
const char *ssid = APSSID;
const char *password = APPSK;
const char* host = "djxmmx.net";
const uint16_t port = 17;

ESP8266WebServer server(80);
void handleRoot() 
{
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

void handletho()
{
  
  server.send(200, "text/html", "<h1>thotho</h1>");
}

void setup() {
  delay(1000);
  Serial.begin(115200);

  //access point
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);


  //station code
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
//  WiFi.mode(WIFI_STA);
//  WiFi.begin(ssid, password);
//
//  while (WiFi.status() != WL_CONNECTED) 
//  {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());

  //Server config
  server.on("/", handleRoot);
  server.on("/tho", handletho);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() 
{
  server.handleClient();
}
