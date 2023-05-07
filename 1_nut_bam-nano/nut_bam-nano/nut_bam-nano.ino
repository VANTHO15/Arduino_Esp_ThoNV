volatile int a = 0, b = 0;
#define  nut2 2
#define  nut3 3
void   vantho2();
void   vantho3();
void setup()
{
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(nut2, INPUT_PULLUP);
  pinMode(nut3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), vantho2, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), vantho3, FALLING);
}

void loop()
{

  digitalWrite(8, a);
  digitalWrite(9, b);
}
void   vantho2()
{
//  delay(50);
//  while(digitalRead(2)==0);
//  delay(50);
  a = !a;
  Serial.print("a=");
  Serial.println(a);
}
void   vantho3()
{
//   delay(50);
//  while(digitalRead(3)==0);
//  delay(50);
  b = !b;
  Serial.print("b=");
  Serial.println(b);
}
