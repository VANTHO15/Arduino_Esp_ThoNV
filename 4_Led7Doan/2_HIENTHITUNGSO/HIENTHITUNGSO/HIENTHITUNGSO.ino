
char digi[10] = {0XC0, 0XF9, 0XA4, 0XBD, 0X99, 0X92, 0X82, 0X8F, 0X80, 0X90};
void hienthi(int n)
{
  char num = digi[n];
  for (int j = 2; j < 9; j++)
  { char X = num & 0X01;
    digitalWrite(j, X);
    num = num >> 1;
  }
}
void setup() {
  // put your setup code here, to run once:
  for (int i = 2; i < 9; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}
int n=34;
void loop() {
  // put your main code here, to run repeatedly:
  for (int n = 0; n < 100; n++)
{
  int  hc = n / 10; int dv = n % 10;
  for (int j = 0; j < 50; j++)
    {
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      hienthi(dv);
      delay(10);
      digitalWrite(11, HIGH);
      digitalWrite(10, LOW);
      hienthi(hc);
      delay(10);
    }
  }
}
