int a[10] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};
void setup()
{
  for (int i = 3; i <= 10; i++)
  { pinMode(i, OUTPUT);
    digitalWrite(i, 1);
  }
}
void loop()
{
  for (int i = 0; i <= 9; i++)
  {
    int x = a[i];
    for (int j = 3; j <= 10; j++)
    {
      digitalWrite(j, x & 0x01);
      x = x >> 1;
    }
    delay(1000);
  }
}
