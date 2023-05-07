void setup() {
  Serial.begin(9600);
}
int i = 0, n;
char a[100];
void loop() {
  if (Serial.available())
  {
    i = i + 1;
    a[i] = Serial.read();
  }
  else if (Serial.read() == 'j' || Serial.read() == 'J')
    for (n = 1; n <= i; n++)
      Serial.print(a[n]);



}
