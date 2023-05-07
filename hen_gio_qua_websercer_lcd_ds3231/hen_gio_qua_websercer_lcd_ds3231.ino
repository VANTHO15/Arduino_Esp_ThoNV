y h#include <ESP8266WiFi.h>
#include "./DNSServer.h"  
#include <ESP8266WebServer.h>
#include <RtcDS3231.h>
#include <Wire.h> // must be included here so that Arduino library object file references work
RtcDS3231<TwoWire> Rtc(Wire);
#include <LiquidCrystal_I2C.h>

const byte        DNS_PORT = 53;          // 53 is set as DNS port
IPAddress         apIP(10, 10, 10, 1);    // Network Server
DNSServer         dnsServer;              // DNS server object
ESP8266WebServer  webServer(80);          // Webserver object 
#define buzzer D8
LiquidCrystal_I2C lcd(0x27, 16, 2);
String hr,minut ;
int hr1, minut1;
String new_time;

/*START OF HMTL CODE*/
String style_detials =  //This String defines the style attributes for webpage
   "<style type=\"text/css\">"
   " body{"
    "  background-color: #a69695;"
    "}"
    "button{"
     " display: inline-block;"
    "}"
    "#buttons{"
     " text-align: center;"
    "}"

    ".controllButtons{"
     " margin-top: 15px;"
      "margin-left: 5px;"
      "background-color: white;"
      "padding: 10px;"
      "border:1px solid black;"
      "border-radius: 10px;"
      "cursor: pointer;"
      "font-size: 14px;"
    "}"

    ".controllButtons:hover{"
     " background-color: orange;"
      "padding: 10px;"
      "border:1px solid black;"
      "border-radius: 10px;"
      "cursor: pointer;"
      "font-size: 14px;"
    "}"

    "@media only screen and (max-width: 700px) {"
     " button{"
      "  display: block;"
      "}"
      "#buttons{"
       " margin-top: 10%;"
        "margin-left: 35%;"
      "}"
       " .controllButtons{"
        "  margin-top: 15px;"
        "margin-left: 5px;"
        "background-color: white;"
        "padding: 15px;"
        "border:1px solid black;"
        "border-radius: 10px;"
        "cursor: pointer;"
        "font-size: 16px;"
      "}"

      ".controllButtons:hover{"
       " background-color: orange;"
        "padding: 15px;"
        "border:1px solid black;"
        "border-radius: 10px;"
        "cursor: pointer;"
        "font-size: 16px;"
      "}"
    "}"

  "</style>";
 

String home_screen = "" //Page 1 - Home Screen HTML code
                      "<!DOCTYPE html><html>"
                      "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
                      + style_detials +
                      "<body><h1>IoT Alarm Clock</h1>"
                      "<div id=\"login\">"
                      "  <form action=\"confirmation_screen.php\" method=\"get\">"
                      "  <h2>Please enter your next Alarm in format (05:45)</h2>"
                      "   <div>Alarm Time: <input type=\"numeric\" name=\"code\" autofocus></div>"
                      "   <div id=\"submit\"><input type=\"submit\" value=\"Submit\"></div>"
                      "  </form>"
                      "</div>"
                      "</body></html>

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
  alarm();
}

void alarm () 
{
    RtcDateTime now = Rtc.GetDateTime();
    lcd.setCursor(0,0);
    lcd.print("Time:");
    lcd.print(now.Hour(), DEC);
    lcd.print(':');
    lcd.print(now.Minute(), DEC);
    lcd.print(':');
    lcd.print(now.Second(), DEC);
    lcd.setCursor(0,1);
    lcd.print("Alarm Time:");
    lcd.print(hr1);
    lcd.print(':');
    lcd.print(minut1);
   
    if( now.Hour() == hr1 && now.Minute() == minut1) //Comparing the current time with the Alarm time

    {
    
    Buzzer();
    Buzzer();
    lcd.clear();
    
    lcd.print("Alarm ON");
    
    lcd.setCursor(0,1);
    
    lcd.print("Alarming");
    Buzzer();
    Buzzer();
   
    
    } 
  }
    
void Buzzer()
    {
    digitalWrite(buzzer,HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
}
