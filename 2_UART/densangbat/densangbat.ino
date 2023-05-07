void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(11, INPUT_PULLUP);
}

void loop() {
  
  if (Serial.available() != 0)
  {
    int a = Serial.read();
    if (a == 49)  digitalWrite(13, HIGH);
    else     if (a == 48)   digitalWrite(13, LOW);
  }
  if (digitalRead(11) == 0)
  {
    delay(50);
    while (digitalRead(11) == 0);
    delay(50);
    digitalWrite(13, !digitalRead(13));
    if (digitalRead(13) == 1)   Serial.println("on");
    else                     Serial.println("off");
  }
}
