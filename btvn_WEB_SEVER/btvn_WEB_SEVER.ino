#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "Vantho15";
const char *password = "12345678";
int stateLED = LOW;

ESP8266WebServer server(80); //Server on port 80

void handleRoot()
{
  response();
}

//void handleLedOff(){
//  stateLED = HIGH;
//  digitalWrite(LED_BUILTIN, stateLED);
//  response();
//}

void response()
{
  String htmlRes = "<html><head>";
  htmlRes += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />";
  htmlRes += "<h2 style=\"text-align: center;\">ESP8266WebServer Control Led</h2><br/>\n";
  if (stateLED == 0)
  {
    htmlRes += "<big>LED is now <b>ON</b></big><br/>\n";
  } else
  {
    htmlRes += "<big>LED is now <b>OFF</b></big><br/>\n";
  }

  htmlRes += "<a href=\"control?LED=ON\"><button style=\"display: block; width: 100%;\">ON</button></a><br/>";
  htmlRes += "<a href=\"control?LED=OFF\"><button style=\"display: block; width: 100%;\">OFF</button></a><br/>";
  htmlRes += "</head></html>";
  if (isset($_GET['LED']))
  {
    $action = $_GET['LED'];
    if ($action == 'ON')
    {
      stateLED = 0;
      digitalWrite(16, 0);
    }
    else
    {
      stateLED = 1;
      digitalWrite(16, 1);
    }
  }
  server.send(200, "text/html", htmlRes);
}

void setup(void) {
  Serial.begin(115200);
  Serial.println("");
  pinMode(16, OUTPUT);
  digitalWrite(16, stateLED);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  server.on("/control", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();          //Handle client requests
}
