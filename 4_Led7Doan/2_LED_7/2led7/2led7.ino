int a[10] = { 0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};
int  hienthi(int n)
{
  int x = a[n];
  for (int i = 3; i <= 10; i++)
  {
    digitalWrite(i, x & 0x01);
    x = x >> 1;
  }
}
void setup() {
  for (int i = 3; i <= 10; i++)

  { pinMode(i, OUTPUT);
    digitalWrite(i, 0);
  }
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(11, 1);
  digitalWrite(12, 1);
  

}

void loop() {
int  b=analogRead(A0); float m=(b*5.0)/1023;int n=m*10;
int  dv=n%10; int hc=n/10;
      digitalWrite(11, 1);
      hienthi(dv);
      digitalWrite(12, 0);
      delay(10); 
      digitalWrite(12, 1);
      hienthi(hc);
      digitalWrite(11, 0);
      delay(10);
}
