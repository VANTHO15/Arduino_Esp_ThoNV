#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "siACVZsamTQGe_TlRvl2mYt21u7dAYJl";
char ssid[] = "Van Tho 15";
char pass[] = "vannhucu";
int virtualPin;
int flag = 0;
//Gửi dữ liệu trạng thái Button từ Blynk về Nodemcu
BLYNK_WRITE(V0)
{
  virtualPin = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("V0 Slider value is: ");
  Serial.println(virtualPin);
  flag = 1;
}
//Đồng bộ lại trạng thái khi mất nguồn
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V0);
}

void setup()
{
  Serial.begin(9600);
  // Blynk.begin(auth, ssid, pass);
  // Blynk.begin(auth, “your_host”, 8080);
  Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 1, 13), 8080);
  pinMode(16, OUTPUT);
  pinMode(0, INPUT_PULLUP);

}

void loop()
{
  Blynk.run();

  if (flag == 1) {
    if (virtualPin == 0) {
      digitalWrite(16, LOW);
    }
    else digitalWrite(16, HIGH);
  }

  if (digitalRead(0) == LOW)
  {
    while (digitalRead(0) == LOW);
    int ledStatus = digitalRead(16);
    if (ledStatus == 0)
    {
      digitalWrite(16, HIGH);
      Blynk.virtualWrite(V0, 1); //Ghi dữ liệu từ Nodemcu lên Blynk
    }
    else
    {
      digitalWrite(16, LOW);
      Blynk.virtualWrite(V0, 0); ////Ghi dữ liệu từ Nodemcu lên Blynk
    }
  }
  flag = 0;
}
