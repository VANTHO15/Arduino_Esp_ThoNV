// https://pubsubclient.knolleary.net/api.html#connect1
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>
// Update these with values suitable for your network.
#define ssid "TAPIT"
#define password "tapit168"
#define mqtt_server "postman.cloudmqtt.com"
#define mqtt_topic_pub "Light"
#define mqtt_topic_sub "Light"
#define mqtt_user "vohhzvgq"
#define mqtt_password "Knfs01UxvKuU"
const uint16_t mqtt_port = 11626;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int a = 0;
void setup() {
  Serial.begin(115200);
  pinMode(16, OUTPUT);
  pinMode(0, INPUT);
  digitalWrite(16, LOW);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
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
  EEPROM.write(0, payload[1]);
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
  else
  {
    Serial.println(" Khong hop le");
    Serial.println();
  }
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(mqtt_topic_pub, "ESP_reconnected");    //gui len mess
      // ... and resubscribe
      client.subscribe(mqtt_topic_sub);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop()
{
  if (a == 0)
  {
    if (EEPROM.read(0) == 'N')
    {
      digitalWrite(16, 0);
      client.publish(mqtt_topic_pub, "DONG_BO_LED_ON");
    }
    if (EEPROM.read(0) == 'F')
    {
      digitalWrite(16, 1);
      client.publish(mqtt_topic_pub, "DONG_BO_LED_OFF");
    }
  }
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  if (digitalRead(0) == 0)
  {
    delay(50);
    while (digitalRead(0) == 0);
    delay(50);
    if (digitalRead(16) == 0)
    {
      digitalWrite(16, 1);
      client.publish(mqtt_topic_pub, "LED_OFF");
    }
    else
    {
      digitalWrite(16, 0);
      client.publish(mqtt_topic_pub, "LED_ON");
    }
  }
  a = 1;
}
