#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <SoftwareSerial.h> //2.5.0
const byte RX = D6;
const byte TX = D5;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);
MDNSResponder mdns;
ESP8266WebServer server(80);

String inputString = "";
bool stringComplete = false;

int bien = 0;
String ChuoiGuiUno = "";
int bien1 = 0;
long last = 0;

String A = "A";
String B = "B";
int nhietdo = 0;
int doam = 0;
int anhsang = 0;
int trangthairelay1 = 0;
int trangthairelay2 = 0;

const char* ssid = "Bao Truc";
const char* pass = "24682468";

const char* www_username = "admin";
const char* www_password = "123456";
const char* www_realm = "Custom Auth Realm";
String authFailResponse = "Authentication Failed";
String text1;
String text2;

String ChuoiSendWebJson = "";

const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Webserver</title>
</head>

<style>
.button {
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}

.button1 {background-color: #4CAF50;} /* Green */
.button2 {background-color: #008CBA;} /* Blue */


.range{
  height: 80px;
  width: 380px;
  background: #fff;
  border-radius: 10px;
  padding: 0 65px 0 45px;
  box-shadow: 2px 4px 8px rgba(0,0,0,0.1);
}
.sliderValue{
  position: relative;
  width: 100%;
}
.sliderValue span{
  position: absolute;
  height: 45px;
  width: 45px;
  transform: translateX(-70%) scale(0);
  font-weight: 500;
  top: -40px;
  line-height: 55px;
  z-index: 2;
  color: #fff;
  transform-origin: bottom;
  transition: transform 0.3s ease-in-out;
}
.sliderValue span.show{
  transform: translateX(-70%) scale(1);
}
.sliderValue span:after{
  position: absolute;
  content: '';
  height: 100%;
  width: 100%;
  background: #664AFF;
  border: 3px solid #fff;
  z-index: -1;
  left: 50%;
  transform: translateX(-50%) rotate(45deg);
  border-bottom-left-radius: 50%;
  box-shadow: 0px 0px 8px rgba(0,0,0,0.1);
  border-top-left-radius: 50%;
  border-top-right-radius: 50%;
}
.field{
  display: flex;
  align-items: center;
  justify-content: center;
  height: 100%;
  position: relative;
}
.field .value{
  position: absolute;
  font-size: 18px;
  color: #664AFF;
  font-weight: 600;
}
.field .value.left{
  left: -22px;
}
.field .value.right{
  right: -43px;
}
.range input{
  -webkit-appearance: none;
  width: 100%;
  height: 3px;
  background: #ddd;
  border-radius: 5px;
  outline: none;
  border: none;
  z-index: 2222;
}
.range input::-webkit-slider-thumb{
  -webkit-appearance: none;
  width: 20px;
  height: 20px;
  background: red;
  border-radius: 50%;
  background: #664AFF;
  border: 1px solid #664AFF;
  cursor: pointer;
}
.range input::-moz-range-thumb{
  -webkit-appearance: none;
  width: 20px;
  height: 20px;
  background: red;
  border-radius: 50%;
  background: #664AFF;
  border: 1px solid #664AFF;
  cursor: pointer;
}
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
     console.log(DataVDK);
     var DataJson = JSON.parse(DataVDK);
     //hiển thị nhiệt độ  
    document.getElementById("nhietdo").innerHTML = DataJson.nhietdo;
     
    // hiển thị độ ẩm 
    document.getElementById("doam").innerHTML = DataJson.doam;
     
  
    // hiển thị trạng t
    
    if(DataJson.relay1 == 0)
    {
      // hiển thị OFF relay
      document.getElementById("trangthairelay1").innerHTML = "OFF";
      
    }
    else if(DataJson.relay1 == 1)
    {
      // hiển thị On relay
      document.getElementById("trangthairelay1").innerHTML = "ON";
    }
  
  if(DataJson.relay2 == 0)
    {
      // hiển thị OFF relay
      document.getElementById("trangthairelay2").innerHTML = "OFF";
      
    }
    else if(DataJson.relay2 == 1)
    {
      // hiển thị On relay
      document.getElementById("trangthairelay2").innerHTML = "ON";
    }
     }         
  }
  xhttp.open('GET','/sendwebserver',true);
  xhttp.send(); 
  // tự update webserver
  setTimeout(function(){ UpdateData() }, 1000);
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
  // lấy dữ liệu từ input ( textbox)
  var Datagui1 = "E" + document.getElementById("ssid").value +"F";
    xhttp.open("GET","/sendtext1?text1="+Datagui1,true);  
    xhttp.send();
 }
function sendtext2()
 {
    var xhttp = new XMLHttpRequest();
  var Datagui2 = "G" + document.getElementById("pass").value + "H";
  
  
    xhttp.open("GET","/sendtext2?text2="+Datagui2,true);         
    xhttp.send();
 }


 function myFunctionRange()
  {
  var textrange = document.getElementById("myRange").value;
  console.log(textrange);
  var xhttp = new XMLHttpRequest();
  var Datagui3 = "J" + textrange + "K";
    xhttp.open("GET","/sendtext3?text3="+Datagui3,true);         
    xhttp.send();
  }
</script>
<body>

<h1>Hello Webserver esp8266</h1>
<h1>Hello lớp học IOT</h1>
</br>
</br>
<h1>Button OnClick 1</h1>
<button class="button button1" type="button" onclick = "onclick1()">OnClick 1</button>


<h1>Button OnClick 2</h1>
<button class="button button2" type="button" onclick = "onclick2()">OnClick 2</button>



<h1> text1:
<input id="ssid"/>
 </h1>
 <button id="button_save"  onclick="sendtext1()">Send text</button>

<h1>text2: 
<input id="pass"/>
</h1>

<button id="button_save"  onclick="sendtext2()">Send text</button>



<div class="range">
    <div class="field">
      <div class="value left">0</div>
      <input id="myRange" type="range" min="0" max="200" value="0" steps="1" oninput="num.value = this.value" > 
      <div class="value right">
      <output id="num">0</output>
      </div>
    </div>
    </br>
    </br>
    <button id="button_save3"  onclick="myFunctionRange()">Send range</button>
    </br>
    </br>
    </br>
    </br>
    </br>
    </br>
  </div>
 </br>
    </br>
    </br>

<h1>Data VDK:
  <label id= 'datavdk'>0</label> 
</h1>
<h1>Trạng Thái Relay 1:
  <label id= 'trangthairelay1'>OFF</label> 
</h1>

<h1>Trạng Thái Relay 1:
  <label id= 'trangthairelay2'>OFF</label> 
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
int bienbutton1 = 0;
int bienbutton2 = 0;
int bientext1 = 0;
int bientext2 = 0;

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  mySerial.begin(9600);
  while (!mySerial);

  pinMode(16, OUTPUT);
  pinMode(2, OUTPUT); 
  WiFi.disconnect();

 // WiFi.config(ip, gateway, subnet);
  
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("connect wifi");
  Serial.print("Address IP esp: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    if (!server.authenticate(www_username, www_password))
      return server.requestAuthentication(DIGEST_AUTH, www_realm, authFailResponse);
      server.send(200, "text/html", webpage);
  });

  server.on("/", [] {
    server.send(200, "text/html", webpage );
  });
  
// A0B => OFF TB1
// A1B => ON thiết bị1

  server.on("/OnClick1", [] {
    last = millis();
    Serial.println(">> Run OnClick 1");
    // nếu điều khiển ON OFF trên esp
    bienbutton1++;
    if(bienbutton1%2 == 0)
    {
      last = millis();
      Serial.println(">> OFF thiết bị 1");
      mySerial.println("A0B");
      trangthairelay1 = 0;
      digitalWrite(16, HIGH);
    }
    else if(bienbutton1%2 == 1)
    {
      last = millis();
       Serial.println(">> ON thiết bị 1");
       trangthairelay1 = 1;
       mySerial.println("A1B");
        digitalWrite(16, LOW);
    } 
    server.send(200, "text/html", webpage );
  });
  
  server.on("/OnClick2", [] {
    Serial.println(">> Run OnClick 2");
   bienbutton2++;
    if(bienbutton2%2 == 0)
    {
      last = millis();
      Serial.println(">> OFF thiết bị 2");
      mySerial.println("C0D");
      trangthairelay2 = 0;
      // lưu trạng thái EEPROM
      digitalWrite(2, HIGH);
    }
    else if(bienbutton2%2 == 1)
    {
      last = millis();
       Serial.println(">> ON thiết bị 2");
       mySerial.println("C1D");
       trangthairelay2 = 1;
       digitalWrite(2, LOW);
    }

    server.send(200, "text/html", webpage );
  });

// Arduino E F , G H
  server.on("/sendtext1", [] {
    last = millis();
    text1 = server.arg("text1");
    Serial.print("Data text1:");
    Serial.println(text1);
    mySerial.println(text1); // tự uno nhận được và xử lý

    
    server.send(200, "text/html", webpage );
  });


   server.on("/sendtext2", [] {
    last = millis();
    text2 = server.arg("text2");
    Serial.print("Data text2:");
    Serial.println(text2);
    mySerial.println(text2); 
    server.send(200, "text/html", webpage );
  });

   server.on("/sendtext3", [] {
    String  text3  = "";
    text3 = server.arg("text3");
    Serial.print("Data text3:");
    Serial.println(text3);
    server.send(200, "text/html", webpage );
  });


  server.on("/sendwebserver", [] {
    Serial.print("ChuoiSendWebJson:");
    Serial.println(ChuoiSendWebJson);
    server.send(200, "text/html", String(ChuoiSendWebJson) );
  });

   server.begin();
  Serial.println("Start");
  
  last = millis();
}

void loop()
{
  Read_Uart();
  server.handleClient();
  if (millis() - last >= 1000)
  {

    mySerial.println("JK");
    last = millis();
  }
}



void Read_Uart()
{
  while (mySerial.available())// A279B290C315D0E\n
  {
    char inChar = (char)mySerial.read();
    inputString += inChar;
    if (inChar == '\n')
    {
      stringComplete = true;
    }
    if (stringComplete)
    {
      Serial.print("Data nhận Uno:");
      Serial.println(inputString);
  
      // xử lý và đưa lên server
      int TimA , TimB , TimC, TimD, TimE = -1;
      TimA = inputString.indexOf("A");
      TimB = inputString.indexOf("B");
      TimC = inputString.indexOf("C");
      TimD = inputString.indexOf("D");
      TimE = inputString.indexOf("E");
   

        if (TimA >= 0 && TimD >= 0 && TimE >= 0 )
        {
        String ChuoiA, ChuoiB , ChuoiC , ChuoiD = "";
        ChuoiA = inputString.substring(TimA + 1 , TimB);
        ChuoiB = inputString.substring(TimB + 1 , TimC);
        ChuoiC = inputString.substring(TimC + 1 , TimD);
        ChuoiD = inputString.substring(TimD + 1 , TimE);

        nhietdo = ChuoiA.toInt();
        doam = ChuoiB.toInt();
        trangthairelay1 = ChuoiC.toInt();
        trangthairelay2 = ChuoiD.toInt();
        SendDataWeb(String(nhietdo), String(doam), String(trangthairelay1), String(trangthairelay2));
        }
      
      //=============
      inputString = "";
      stringComplete = false;
    }
  }
}


void SendDataWeb( String sensor1 ,  String sensor2 ,  String sensor3 , String sensor4  )
{

  ChuoiSendWebJson = "";
  ChuoiSendWebJson = "{\"nhietdo\":\"" + String(sensor1) + "\","+
                         "\"doam\":\"" + String(sensor2) + "\","+
                      "\"relay1\":\"" + String(sensor3) + "\","+
                       "\"relay2\":\"" + String(sensor4) + "\"}";
}
