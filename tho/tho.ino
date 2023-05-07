void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(11, INPUT_PULLUP);
}
int a = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(11) == 0)
  {
      delay(50);
    while (digitalRead(11) == 0)
      delay(50);
    if (a == 0)
    {
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13,LOW);
      delay(100);
    }
    else
    {
      digitalWrite(13, HIGH);
      delay(2000);
      digitalWrite(13,LOW);
      delay(100);
    }
    a = !a;
  }
}
