byte a[10] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};
void setup()
{
  for (int i = 3; i <= 10; i++)
  {
    pinMode(i, OUTPUT);

  }
  pinMode(2, INPUT_PULLUP);
}
int j = -1;
void loop()
{
  if (digitalRead(2) == 0)
  {
    if (j == 0) j = j + 1;
    if (j == 9) j = j - 1;

    delay(50);
    while (digitalRead(2) == 0);
    delay(50);

    int x = a[j];
    for (int i = 3; i <= 10; i++)
    {
      digitalWrite(i, x & 0x01);
      x = x >> 1;

    }

  }
}
