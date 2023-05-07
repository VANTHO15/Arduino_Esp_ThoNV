#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* mqtt_server = "mqtt.ngoinhaiot.com";
const char* mqtt_user = "toannv10291";
const char* mqtt_pass = "toannv10291";
int mqtt_port = 1111; // esp kết nối mqtt => TCP
String topicsub = "toannv10291/quat"; // nhận dữ liệu
String topicpub = "toannv10291/maylanh"; // gửi dữ liệu

WiFiClient espClient;
PubSubClient client(espClient);

#define Led1 16
#define Led2 2
// khai báo id mk wifi nhà mình
const char* ssid = "Bao Truc";
const char* pass = "24682468";

String Data = "";
unsigned long last = 0;
int trangthairelay1 = 0;
int trangthairelay2 = 0;
String ChuoiSendMQTT = "";
int nhietdo = 0;
int doam = 0;
int anhsang = 0;
long bien1 = 0;
long bien2 = 0;
void callback(char* topic, byte* payload, unsigned int length)
{
  for (int i = 0; i < length; i++)
  {
    Data += (char)payload[i];
  }
  Serial.print("Data nhận = ");
  Serial.println(Data);
  delay(100);
  //==================================
  // mỗi esp xử lý cho esp

  // A1B ON 1 , A0B OFF1
  if (Data.indexOf("A1B") >= 0)
  {
    Serial.println("ON thiết bị 1");
    digitalWrite(16, HIGH);
    trangthairelay1 = 1;
  }
  else if (Data.indexOf("A0B") >= 0)
  {
    Serial.println("OFF thiết bị 1");
    digitalWrite(16, LOW);
    trangthairelay1 = 0;
  }
  // C1D ON 2 , C0D OFF 2
  else if (Data.indexOf("C1D") >= 0)
  {
    Serial.println("ON thiết bị 2");
    digitalWrite(2, HIGH);
    trangthairelay2 = 1;
  }
  else if (Data.indexOf("C0D") >= 0)
  {
    Serial.println("OFF thiết bị 2");
    digitalWrite(2, LOW);
    trangthairelay2 = 0;
  }
  // xử lý dữ liệu
  // E[dữ liệu]F
  /*
        Bước 1: tìm kí tự A B trong chuỗi gửi xuống
        Bước 2: Tách dữ liệu
        Bước 3: gán dữ liệu cho 1 cái biến
  */
  //EF
  int TimE, TimF = -1;
  TimE = Data.indexOf("E");
  TimF = Data.indexOf("F");
  if (TimE >= 0 && TimF >= 0)
  {
    String text1 = "";
    text1 = Data.substring(TimE + 1 , TimF);
    bien1 = text1.toInt();
    Serial.println(bien1);
  }

  //GH
  int TimG, TimH = -1;
  TimG = Data.indexOf("G");
  TimH = Data.indexOf("H");
  if (TimG >= 0 && TimH >= 0)
  {
    String text2 = "";
    text2 = Data.substring(TimG + 1 , TimH);
    bien2 = text2.toInt();
    Serial.println(bien2);
  }
  // nếu giao tiếp UNO MEGA , stm
  // gửi dữ liệu qua chíp kia bằng UART
  // mySerial.println(Data);

  //==================================
  Data = "";
}
void ConnectMqttBroker()
{
  client.setServer(mqtt_server, mqtt_port); // sét esp client kết nối MQTT broker
  delay(10);
  client.setCallback(callback); // => đọc dữ liệu mqtt broker
  delay(10);
}
// Nhận dữ liệu từ Server MQTT Broker


void reconnect()
{

  while (!client.connected())
  {
    String clientId = "ESP8266Client123";
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass))
    {
      Serial.println("Connected MQTT ngoinhaiot.com");
      client.subscribe(topicsub.c_str());
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}
void setup()
{
  Serial.begin(9600);
  while (!Serial);
  WiFi.mode(WIFI_STA);
  pinMode(2, OUTPUT);
  pinMode(16, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(16, HIGH);
  WiFi.disconnect();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connect wifi");
  ConnectMqttBroker();
  Serial.println("Start ESP");
  last = millis();

}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  if (millis() - last >= 3000)
  {
    dulieucambien();
    SendDataMQTT(String(nhietdo), String(doam), String(anhsang), String(trangthairelay1), String(trangthairelay2) );
    last = millis();
  }
 

}

void dulieucambien()
{
  nhietdo++;
  doam = doam + 2;
  anhsang = anhsang + 3;
}

/*
   if (millis() - last >= 3000)
  {
    nhietdo++;
    doam = doam + 2;
    anhsang = anhsang + 3;
    SendDataMQTT(String(nhietdo), String(doam), String(anhsang), String(trangthairelay1));
    last = millis();
  }
*/


void SendDataMQTT( String sensor1 ,  String sensor2 ,  String sensor3 , String sensor4, String sensor5 )
{
  // Data json {"nhietdo":"giatrinhietdo", "doam":"giatridoam" , "anhsang":"giatrianhanh","relay1":"trangthairelay1"}
  //String html ="{\"nhietdo\":\"giatrinhietdo\", \"doam\":\"giatridoam\" , \"anhsang\":\"giatrianhanh\",\"relay1\":\"trangthairelay1\"}";
  //"{\"nhietdo\":\" ", \"doam\":\"giatridoam\" , \"anhsang\":\"giatrianhanh\"}";
  //\"nhietdo\":\"giatrinhietdo\" => \"nhietdo\":\"\" => \"nhietdo\":\""+ String(sensor1)+"\"
  ChuoiSendMQTT = "";
  // ChuoiSendWebJson = "{\"nhietdo\":\"" + String(sensor1) + "\",\"doam\":\"" + String(sensor2) + "\",\"anhsang\":\"" + String(sensor3) + "\",\"relay1\":\"" + String(sensor4) + "\"}";
  ChuoiSendMQTT = "{\"nhietdo\":\"" + String(sensor1) + "\"," +
                  "\"doam\":\"" + String(sensor2) + "\"," +
                  "\"anhsang\":\"" + String(sensor3) + "\"," +
                  "\"relay1\":\"" + String(sensor4) + "\"," +
                  "\"relay2\":\"" + String(sensor5) + "\"}";

  Serial.print("ChuoiSendMQTT:");
  Serial.println(ChuoiSendMQTT);

  client.publish(topicpub.c_str(), ChuoiSendMQTT.c_str()); //
}
