void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop()
{
  char data;
  if (Serial.available())
  {
    data = Serial.read();
    if (data == 'G') digitalWrite(13, 1);
    if (data == 49) digitalWrite(13, 0);
  }

}
