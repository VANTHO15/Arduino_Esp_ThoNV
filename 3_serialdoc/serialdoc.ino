void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  digitalWrite(13, 1);
}
char x;
void loop() {
  x = Serial.read();
  if (x == '0')
  {
    digitalWrite(13, 1);
    Serial.println("led on");
  }
  else
  if(x=='1')
  {
    digitalWrite(13, 0);
    Serial.println("led off");
  }
}
