
void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT_PULLUP);
}
int a = 1;
void loop()
{

  if (digitalRead(4) == 0)
  {
    delay(50);
    while (digitalRead(4) == 0);
    delay(50);
    a = a + 1;

  }
  if (a % 2 == 0)
  {
    Serial.println("sang");
    digitalWrite(3, 1);
    digitalWrite(2, 0);
  }
  else
   digitalWrite(3, 0);
    digitalWrite(2, 1);
  
}
