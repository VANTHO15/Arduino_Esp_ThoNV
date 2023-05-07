void setup() {

  pinMode(13, OUTPUT);
  digitalWrite(13, 1);
  pinMode(10, INPUT_PULLUP);
}
int a = 0;
void loop() {

  if (digitalRead(10) == 0)
  {
    delay(50);
    while (digitalRead(10) == 0);
    delay(50);
    a = a + 1;


    if (a % 2 == 0)
      digitalWrite(13, !digitalRead(13));
  }
}
