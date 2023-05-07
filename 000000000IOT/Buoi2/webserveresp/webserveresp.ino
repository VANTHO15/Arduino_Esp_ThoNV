#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);

const char* ssid = "Bao Truc";
const char* pass = "24682468";

#define LED1 2
#define LED2 16

int trangthairelay1 = 0;
int trangthairelay2 = 0;

int bien = 0;
int bien1 = 0;
int bien2 = 0;
const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<meta charset="utf-8">
<title>
Lớp học IOT - webserver
</title>

<style>
.button {
  border: none;
  color: white;
  padding: 20px 100px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}

.button1 {background-color: #ff0000;} /* Green */
.button2 {background-color: #008CBA;} /* Blue */
</style>


<script>

function onclick1()
{
  var xhttp = new XMLHttpRequest();
  xhttp.open('GET','/OnClick1',true);
  xhttp.send();
}

function onclick2()
{
  var xhttp = new XMLHttpRequest();
  xhttp.open('GET','/OnClick2',true);
  xhttp.send();
}

function sendtext1()
{
  var xhttp = new XMLHttpRequest();
  // lấy dữ liệu của input
  var ssid = "E" + document.getElementById("text1").value + "F";
  xhttp.open("GET","/sendtext1?ssid1="+ssid,true);        
  xhttp.send();
}

function sendtext2()
{
  var xhttp = new XMLHttpRequest();
  // lấy dữ liệu của input
  var ssidd = "A" + document.getElementById("text2").value + "B";
  xhttp.open("GET","/sendtext2?ssid2="+ssidd,true);        
  xhttp.send();
}





</script>

<body>


<h1>Hello Webserver esp8266</h1>
<h1>Hello lớp học IOT</h1>
</br>
</br>

<h1>Button 1 điều khiển thiết bị 1</h1>
<button class="button button1" type="button" onclick = "onclick1()">OnClick 1</button>
<h1>Button 2 điều khiển thiết bị 2</h1>
<button class="button button2" type="button" onclick = "onclick2()">OnClick 2</button>

<h1> text1:
<input id="text1"/>
<button  type="button" onclick = "sendtext1()">Send text 1</button>
</h1>

<h1> text2:
<input id="text2"/>
<button  type="button" onclick = "sendtext2()">Send text 2</button>
</h1>
</body>
</html>
)=====";



void setup()
{
  Serial.begin(9600);
  while (!Serial);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  WiFi.mode(WIFI_AP_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("Connect WiFi");
  Serial.print("Address IP esp: ");
  Serial.println(WiFi.localIP());
  server.on("/", [] {
    server.send(200, "text/html", webpage );
  });

  server.on("/OnClick1", [] {
    Serial.println(">>Onclick button 111111");
    
    bien++;
    Serial.print("bien:"); 
    Serial.println(bien);
    if(bien%2 == 1)
    {
      Serial.println(">>ON LED 1");
      digitalWrite(LED1, LOW);
      trangthairelay1 = 1;
    }
    else
    {
      Serial.println(">>OFF LED 1");
      digitalWrite(LED1, HIGH);
      trangthairelay1 = 0;
    }
    server.send(200, "text/html", webpage );
  });


  

   server.on("/OnClick2", [] {
    Serial.println(">>Onclick button 222222");
    if(trangthairelay2 == 0)
    {
      Serial.println(">>ON LED 2");
      trangthairelay2 = 1;
      digitalWrite(LED2, HIGH);
    }
    else if(trangthairelay2 == 1)
    {
      Serial.println(">>OFF LED 2");
      trangthairelay2 = 0;
      digitalWrite(LED2, LOW);
    }
    server.send(200, "text/html", webpage );
  });
  


  server.on("/sendtext1", [] {
    Serial.println(server.arg("ssid1"));
    // gửi uno mySerial.println(server.arg("ssid1"));
    // xử lý cho esp
    String text1 = "";
    text1 = server.arg("ssid1");
    Serial.print("text1:");
     Serial.println(text1);
    server.send(200, "text/html", webpage );
  });


  server.on("/sendtext2", [] {
    Serial.println(server.arg("ssid2"));
     // gửi uno mySerial.println(server.arg("ssid2"));
    server.send(200, "text/html", webpage );
  });
  
  server.begin();

  Serial.println("Server start");

  
}

void loop() 
{
  
  server.handleClient();

}




void SendDataWeb( String sensor1 ,  String sensor2 ,  String sensor3 , String sensor4 )
{
  // Data json {"nhietdo":"giatrinhietdo", "doam":"giatridoam" , "anhsang":"giatrianhanh"}
  //"{\"nhietdo\":\" ", \"doam\":\"giatridoam\" , \"anhsang\":\"giatrianhanh\"}";
  String ChuoiSendWebJson = "";
 // ChuoiSendWebJson = "{\"nhietdo\":\"" + String(sensor1) + "\",\"doam\":\"" + String(sensor2) + "\",\"anhsang\":\"" + String(sensor3) + "\",\"relay1\":\"" + String(sensor4) + "\"}";
  ChuoiSendWebJson = "{\"nhietdo\":\"" + String(sensor1) + "\","+
                         "\"doam\":\"" + String(sensor2) + "\","+
                      "\"anhsang\":\"" + String(sensor3) + "\","+
                       "\"relay1\":\"" + String(sensor4) + "\"}";

 //Serial.print("ChuoiSendWebJson:");
  //Serial.println(ChuoiSendWebJson);
}
