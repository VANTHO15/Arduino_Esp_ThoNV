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
long last = 0;
int nhietdo = 0;
int doam = 0;
int anhsang = 0;
String ChuoiSendWebJson = "";

const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<meta charset="utf-8">
<title>Lớp học IOT - webserver</title>

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
function UpdateData(){
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function (){
     if(this.readyState == 4 && this.status == 200){
    var DataVDK  = xhttp.responseText;
    console.log("Dữ liệu VDK:" + DataVDK);
    var DataJson = JSON.parse(DataVDK);
    document.getElementById("datavdk").innerHTML = DataVDK;
    document.getElementById("nhietdo").innerHTML = DataJson.nhietdo;
    document.getElementById("doam").innerHTML = DataJson.doam;
    document.getElementById("anhsang").innerHTML = DataJson.anhsang;
  
    if(DataJson.relay1 == 0){
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
  //
   var today = new Date();
  var h = today.getHours();
  var m = today.getMinutes();
  var s = today.getSeconds();
  m = checkTime(m);
  s = checkTime(s);
  var ChuoiThoiGian = h + ":" + m + ":" + s;
  console.log("Thời Gian:" + ChuoiThoiGian);
  console.log("Date:" + today);
  // tự update webserver
  setTimeout(function(){ UpdateData() }, 500);
}

function checkTime(i) {
  if (i < 10) {
    i = "0" + i;
  }
  return i;
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

<h1>text1:<input id="text1"/><button  type="button" onclick = "sendtext1()">Send text 1</button></h1>

<h1>text2:<input id="text2"/><button  type="button" onclick = "sendtext2()">Send text 2</button></h1>

<h1>Data VDK:<label id= 'datavdk'>0</label> </h1>

<h1>Ánh sáng:<label id= 'trangthairelay1'>OFF</label></h1>

<h1>Nhiệt Độ:<label id= 'nhietdo'>0</label></h1>

<h1>Độ Ẩm:<label id= 'doam'>0</label></h1>
 
<h1>Ánh sáng:<label id= 'anhsang'>0</label></h1>


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
    
  </div>
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
    // mySerial.println();
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

  
}

void loop() 
{
  
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
