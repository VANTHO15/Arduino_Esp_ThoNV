byte a[10] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};
void setup()
{
  for (int i = 3; i <= 10; i++)
  {
    pinMode(i, OUTPUT);

  }

}
void loop()
{
  for (int j = 0; j <= 9; j++)
  {
    int x = a[j];
    for (int i = 3; i <= 10; i++)
    {
      digitalWrite(i, x & 0x01);
      x = x >> 1;

    }
    delay(1000);
  }
}
