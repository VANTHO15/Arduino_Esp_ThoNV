//----------------------------------------Include the NodeMCU ESP8266 Library
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//----------------------------------------

#include "PageIndex.h" //--> Include the contents of the User Interface Web page, stored in the same folder as the .ino file

#define ON_Board_LED 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router
#define LIGHT 5 //--> Defining LIGHT Port

//----------------------------------------SSID and Password of your WiFi router
const char* ssid = "VanTho15";  //--> Your wifi SSID Name
const char* password = "vannhucu"; //--> Your wifi Password
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
  
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  pinMode(LIGHT,OUTPUT); //--> LIGHT port Direction output
  
  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //----------------------------------------
 
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
