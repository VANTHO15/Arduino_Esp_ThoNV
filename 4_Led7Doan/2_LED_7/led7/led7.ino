char digi[10] = {0XC0, 0xF9, 0XA4, 0XBD, 0X99, 0X82, 0XF8, 0X80, 0X90};
void setup() {
  // put your setup code here, to run once:
  for (int i = 2; i < 9; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int n = 0; n < 10; n++)
  {
    char num = digi[n];
    for (int j = 2; j < 9; j++)
     { char X = num & 0X01;
    digitalWrite(j, X);
    num = num >> 1;
  }
  delay(1000);
}
}
