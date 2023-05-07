void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT_PULLUP);
}
int a = 1;
void loop()
{
  if (digitalRead(2) == 0) {
    delay(50);
    while(digitalRead(2)==0);
    delay(50);
    a = a + 1;
    if (a % 2 == 1)
    {
      digitalWrite(13, 1);
      Serial.println("led sang");
    }
    else
    {
      digitalWrite(13, 0);
      Serial.println("led tat");
    }
  }
}
