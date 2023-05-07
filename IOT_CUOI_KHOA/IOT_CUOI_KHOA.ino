#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <NTPtimeESP.h>
NTPtime NTPch("ch.pool.ntp.org");   // Server NTP
strDateTime dateTime;
#define ssid "Van Tho 15"
#define password "vannhucu"
#define mqtt_server " 192.168.1.13"
#define mqtt_topic_pub "Light/state"
#define mqtt_topic_sub "Light/command"
#define mqtt_user "vohhzvgq"
#define mqtt_password "Knfs01UxvKuU"
const uint16_t mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(16, OUTPUT);
  pinMode(0, INPUT);
  digitalWrite(16, LOW);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}
void setup_wifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String s = "";
  for (int i = 0; i < length; i++)
  {
    char p = (char)payload[i];
    s = s + p;
  }
  if (s == "ON")
  {
    digitalWrite(16, LOW);
    Serial.println(" Turn On LED! " );
  }
  else if (s == "OFF")
  {
    digitalWrite(16, HIGH);
    Serial.println(" Turn Off LED! " );
  }
  else Serial.println(" Khong hop le");
  Serial.println();
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password))
    {
      Serial.println("connected");
      client.publish(mqtt_topic_pub, "ESP_reconnected");    //gui len mess
      client.subscribe(mqtt_topic_sub);
    } else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
void loop()
{
  if (!client.connected())                     //connect
  {
    reconnect();
  }
  dateTime = NTPch.getNTPtime(7.0, 0);         // lay time
  if (dateTime.valid)
  {
    NTPch.printDateTime(dateTime);
    byte actualHour = dateTime.hour;      
    byte actualMinute = dateTime.minute;   
    byte actualsecond = dateTime.second;   
    int actualyear = dateTime.year;        
    byte actualMonth = dateTime.month;     
    byte actualday = dateTime.day;         
    byte actualdayofWeek = dateTime.dayofWeek;
    Serial.println(actualMinute);
  }
  if (digitalRead(0) == 0)
  {
    delay(50);
    while (digitalRead(0) == 0);
    delay(50);
    if (digitalRead(16) == 0)
    {
      digitalWrite(16, 1);
      client.publish(mqtt_topic_pub, "OFF");
    }
    else
    {
      digitalWrite(16, 0);
      client.publish(mqtt_topic_pub, "ON");
    }
  }
  client.loop();
}
