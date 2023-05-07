void setup()
{
  pinMode(0, INPUT_PULLUP);
  pinMode(16, OUTPUT);
  digitalWrite(16, 1);

}

void loop()
{
  while (digitalRead(0) == 0)
    digitalWrite(16, 0);
  digitalWrite(16, 1);
}
