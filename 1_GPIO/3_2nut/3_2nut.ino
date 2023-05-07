volatile int a = 0;
#define  nut2 2
void   vantho2();
void setup()
{
  pinMode(5, OUTPUT);
  pinMode(nut2, INPUT_PULLUP);
  pinMode(nut3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), vantho2, FALLING);
}

void loop()
{

  digitalWrite(5, a);
}
void   vantho2()
{
  for (int i = 1; i <= 10000; i++);
  while (digitalRead(2) == 0);
  for (int i = 1; i <= 10000; i++);
  a = !a;

}
