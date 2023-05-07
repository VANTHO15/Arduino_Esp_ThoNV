volatile int a = 0, b = 0;
#define  nut2 2
#define  nut3 3
void sang(int a)
{
  if (a == 1)  digitalWrite(4, !digitalRead(4));
  if (a == 2)  digitalWrite(5, !digitalRead(5));
  if (a == 3)  digitalWrite(6, !digitalRead(6));
  if (a == 4)  digitalWrite(7, !digitalRead(7));

}
void setup()
{
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(nut2, INPUT_PULLUP);
  pinMode(nut3, INPUT_PULLUP);
}

void loop()
{
  if (digitalRead(2) == 0)
  {
    delay(50);
    while (digitalRead(2) == 0);
    delay(50);
    if (b == 0)
    {
      a++;
      if (a == 5)
      {
        b = 1;
        a = 4;
      }
    }
    else
    {
      a--;
      if (a == 0)
      {
        b = 0;
        a = 1;
      }
    }
    sang(a);
  }
}
