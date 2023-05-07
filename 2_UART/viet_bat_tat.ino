void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}
void loop() {
  String data = Serial.readString();
  if (data.indexOf("bat") != -1)
  {
    digitalWrite(13, HIGH);
    Serial.println("bat");
  }
  if (data.indexOf("tat") != -1 )
  {
    digitalWrite(13, LOW);
    Serial.println("tat");
  }
}
