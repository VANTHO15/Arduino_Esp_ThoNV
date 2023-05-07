#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// Update these with values suitable for your network.
#define ssid "Van Tho 15"
#define password "vannhucu"
#define mqtt_server "192.168.1.13"
#define mqtt_topic_pub "light/state"
#define mqtt_topic_sub "light/command"
#define ter "temperature/state"
#define mqtt_user "vohhzvgq"
#define mqtt_password "Knfs01UxvKuU"
const uint16_t mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);
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
  // if MQTT comes a 1, turn on LED on pin D2
  else if (s == "OFF")
  {
    digitalWrite(16, HIGH);
    Serial.println(" Turn Off LED! " );
  }
  else Serial.println(" Khong hop le");
  Serial.println();
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_user , mqtt_password))
    {
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
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  client.publish(ter, String(32).c_str(), true);
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
}
