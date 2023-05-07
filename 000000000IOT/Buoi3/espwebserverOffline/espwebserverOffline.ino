//----------------------------------------Include the NodeMCU ESP8266 Library
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//----------------------------------------



#define LIGHT 5 //--> Defining LIGHT Port

//----------------------------------------Make a wifi name and password as access point
const char* ssid = "wifi8266";
const char* password = "24682468";
//----------------------------------------

ESP8266WebServer server(80);  //--> Server on port 80

#define LED1 2
#define LED2 16

int trangthairelay1 = 0;
int trangthairelay2 = 0;

int bien = 0;
int bien1 = 0;
int bien2 = 0;
long last = 0;
int nhietdo = 0;
int doam = 0;
int anhsang = 0;
String ChuoiSendWebJson = "";

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
window.onload = UpdateData;
function UpdateData()
{
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function ()
  {
     if(this.readyState == 4 && this.status == 200)
     {
    var DataVDK  = xhttp.responseText;
    console.log("Dữ liệu VDK:" + DataVDK);

    var DataJson = JSON.parse(DataVDK);
    document.getElementById("datavdk").innerHTML = DataVDK;
    document.getElementById("nhietdo").innerHTML = DataJson.nhietdo;
    document.getElementById("doam").innerHTML = DataJson.doam;
    document.getElementById("anhsang").innerHTML = DataJson.anhsang;
    if(DataJson.relay1 == 0)
    {
      document.getElementById("trangthairelay1").innerHTML = "OFF";
    }
    else if(DataJson.relay1 == 1)
    {
      document.getElementById("trangthairelay1").innerHTML = "ON";
    }
     }         
  }
  xhttp.open('GET','/sendweb',true);
  xhttp.send(); 
  // tự update webserver
  setTimeout(function(){ UpdateData() }, 500);
}


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

<h1>Data VDK:
  <label id= 'datavdk'>0</label> 
</h1>
<h1>Thiết Bị 1:
<label id= 'trangthairelay1'>OFF</label>   
</h1>

<h1>Nhiệt Độ:
<label id= 'nhietdo'>0</label>   
</h1>

<h1>Độ Ẩm:
<label id= 'doam'>0</label>  
</h1>
 
<h1>Ánh sáng:
<label id= 'anhsang'>0</label>   
</h1>
</body>




</html>


)=====";
void setup(void)
{
  Serial.begin(9600);
  while (!Serial);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  WiFi.softAP(ssid, password);  //--> Start Making ESP8266 NodeMCU as an access point

  IPAddress apip = WiFi.softAPIP(); //--> Get the IP server
  Serial.print("Connect your wifi laptop/mobile phone to this NodeMCU Access Point : ");
  Serial.println(ssid);
  Serial.print("Visit this IP : ");
  Serial.print(apip); //--> Prints the IP address of the server to be visited
  Serial.println(" in your browser.");
 
 
  
  //=================

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
  // gửi dữ liệu về webserver
  server.on("/sendweb", [] {
    server.send(200, "text/html", String(ChuoiSendWebJson));
  });
  
  server.begin();

  Serial.println("Server start");

  last = millis();

  //==================
}
//----------------------------------------
//----------------------------------------LOOP
void loop(void){
  server.handleClient();
  if(millis() - last >= 3000)
  {
     dulieucambien();
     SendDataWeb(String(nhietdo),String(doam), String(anhsang), String(trangthairelay1), String(trangthairelay2));
     last = millis();
  }
}

void  dulieucambien()
{
  nhietdo = nhietdo + 1;
  doam = doam + 2;
  anhsang = anhsang + 3;
}

void SendDataWeb( String sensor1 ,  String sensor2 ,  String sensor3 , String sensor4 , String sensor5)
{
  
  // Data json {"nhietdo":"giatrinhietdo", "doam":"giatridoam" , "anhsang":"giatrianhanh"}
  //"{\"nhietdo\":\" ", \"doam\":\"giatridoam\" , \"anhsang\":\"giatrianhanh\"}";
   ChuoiSendWebJson = "";
 // ChuoiSendWebJson = "{\"nhietdo\":\""+String(sensor1)+"\",\"doam\":\"" + String(sensor2) + "\",\"anhsang\":\"" + String(sensor3) + "\",\"relay1\":\"" + String(sensor4) + "\"}";
  ChuoiSendWebJson = "{\"nhietdo\":\"" + String(sensor1) + "\","+
                      "\"doam\":\"" + String(sensor2) + "\","+
                      "\"anhsang\":\"" + String(sensor3) + "\","+
                      "\"relay1\":\"" + String(sensor4) + "\","+
                      "\"relay2\":\"" + String(sensor5) + "\"}";

  Serial.print("ChuoiSendWebJson:");
  Serial.println(ChuoiSendWebJson);
}
//----------------------------------------
