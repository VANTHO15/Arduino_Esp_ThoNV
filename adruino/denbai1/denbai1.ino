void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
}
int a = 1;
void loop() {
  // put your main code here, to run repeatedly:
  while (1)
  { if (a % 2 == 1)
    {
      digitalWrite(13, 1);
      delay(1000);
    }
    else
    {
      digitalWrite(13, 0);
      delay(3000);
    }
    a = a + 1;
  }
}
