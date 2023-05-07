int a[10] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};
void setup()
{
  for (int i = 3; i <= 10; i++)
    pinMode(i, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), THO, RISING);
}
volatile int n = 0, j = 0;
void loop()
{
  int x = a[n];
  for (int i = 3; i <= 10; i++)
  {
    digitalWrite(i, x & 0x01);
    x=x >> 1;
  }
}
void  THO()
{
  for(int k=1;k<=5000;k++);
  while (digitalRead(2) == 0);
  for(int k=1;k<=5000;k++);
  if (j == 0)
  {
    n++;
    if (n == 9)
    {
      j = 1;
    }
  }
  else
  {
    n--;
    if (n == 0)
    {
      j = 0;
    }
  }
}
