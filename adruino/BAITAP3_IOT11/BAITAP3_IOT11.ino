void setup() {
  Serial.begin(115200);
  pinMode(16, OUTPUT);
  pinMode(0, INPUT_PULLUP);
}
int a = 1;
void loop()
{
  if (digitalRead(0) == 0)
  {
    delay(50);
    while (digitalRead(0) == 0);
    delay(50);
    a = a + 1;
    if (a % 2 == 1)
    {
      digitalWrite(16, 0);
      Serial.println("led on");
    }
    else
    {
      digitalWrite(16, 1);
      Serial.println("led off");
    }
  }
  if (Serial.available())
  {
    String chuoi = Serial.readString();
    if (chuoi.indexOf("led on") != -1) digitalWrite(16, 0);
    if (chuoi.indexOf("led off") != -1) digitalWrite(16, 1);
  }
}
