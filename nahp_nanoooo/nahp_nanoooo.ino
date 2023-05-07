void vantho(int a, int b, int c)
{
  for (int i = 1; i <= a; i++)
  {
    digitalWrite(c, 1);
    delay(b);
    digitalWrite(c, 0);
    delay(b);
  }

}
void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

}

void loop() {
 vantho(1,100,4);
 vantho(2,100,5);
 vantho(3,100,6);
 vantho(4,100,7);
 

}
