//----------------------------------------Include the NodeMCU ESP8266 Library
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//----------------------------------------

#include "PageIndex.h" //--> Include the contents of the User Interface Web page, stored in the same folder as the .ino file

#define LIGHT 5 //--> Defining LIGHT Port

//----------------------------------------Make a wifi name and password as access point
const char* ssid = "wifi8266";
const char* password = "24682468";
//----------------------------------------

ESP8266WebServer server(80);  //--> Server on port 80

//----------------------------------------This routine is executed when you open NodeMCU ESP8266 IP Address in browser
void handleRoot() {
  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
}
//----------------------------------------
//----------------------------------------Procedure for turning lights on or off
void handleLIGHT() {
  String LightState = "OFF";
  String t_state = server.arg("LIGHTState");
  Serial.print(t_state);
  if(t_state == "1")  {
    digitalWrite(LIGHT,HIGH); //LED ON
    LightState = "ON"; //Feedback parameter
    Serial.println(" | LIGHT ON");
  }
  else  {
    digitalWrite(LIGHT,LOW); //LED OFF
    LightState = "OFF"; //Feedback parameter 
    Serial.println(" | LIGHT OFF"); 
  }
  server.send(200, "text/plane", LightState); //Send web page
}
//----------------------------------------
//----------------------------------------SETUP
void setup(void){
  Serial.begin(115200);
  delay(500);

  pinMode(LIGHT,OUTPUT); //--> LIGHT port Direction output
  
  WiFi.softAP(ssid, password);  //--> Start Making ESP8266 NodeMCU as an access point

  IPAddress apip = WiFi.softAPIP(); //--> Get the IP server
  Serial.print("Connect your wifi laptop/mobile phone to this NodeMCU Access Point : ");
  Serial.println(ssid);
  Serial.print("Visit this IP : ");
  Serial.print(apip); //--> Prints the IP address of the server to be visited
  Serial.println(" in your browser.");
 
  server.on("/", handleRoot); //--> Routine to handle at root location. This is to display web page.
  server.on("/setLIGHT", handleLIGHT);  //--> Routine to handle the call procedure handleLIGHT
  
  server.begin(); //--> Start server
  Serial.println("HTTP server started");
}
//----------------------------------------
//----------------------------------------LOOP
void loop(void){
  server.handleClient();  //--> Handle client requests
}
//----------------------------------------
