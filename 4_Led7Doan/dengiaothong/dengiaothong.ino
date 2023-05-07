int a[10] = { 0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};
int q = 0, p = 1, xanh = 6, doa = 6, vang = 6;
int  hienthi(int n)
{
  int x = a[n];
  for (int i = 3; i <= 10; i++)
  {
    digitalWrite(i, x & 0x01);
    x = x >> 1;
  }
}
int  sang(int a)
{
  
  Serial.println(a);
  digitalWrite(11, 1);
  hienthi(a / 10);
  digitalWrite(12, 0);
  delay(10);
  digitalWrite(12, 1);
  hienthi(a % 10);
  digitalWrite(11, 0);
  delay(10);

}
void setup()
{
  for (int i = 0; i <= 10; i++)

  { pinMode(i, OUTPUT);
    digitalWrite(i, 0);
  }
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(11, 1);
  digitalWrite(12, 1);
  Serial.begin(9600);
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;
  TCCR1B |= 1 << CS12;
  TCNT1 = 3036;
  TIMSK1 = (1 << TOIE1);
  sei();
}

void loop()
{
  if (Serial.available() > 0)
  {
    p = 1;
    String data = Serial.readString();
    String data1 = data.substring(0, 2);
    String data2 = data.substring(2, 4);
    String data3 = data.substring(4, 6);
    xanh = data1.toInt();
    vang = data2.toInt();
    doa = data3.toInt();
  }
  if (q <= xanh-1)
  { 
    sang(xanh -1 - q);
    digitalWrite(A0, 1);
    digitalWrite(A1, 0);
    digitalWrite(A2, 0);
  }
  if ((q > xanh-1) && (q <= (xanh + vang-1) ))
  {
    sang(xanh + vang -1 - q);
    digitalWrite(A0, 0);
    digitalWrite(A1, 1);
    digitalWrite(A2, 0);
  }
  if ((q > (xanh + vang -1)) && (q <= (xanh + vang + doa -1)))
  {
    sang(xanh + vang +doa -1 - q);
    digitalWrite(A0, 0);
    digitalWrite(A1, 0);
    digitalWrite(A2, 1);
  }
  if (q > (xanh + vang + doa -1))
  {
    q = 0;
  }
  
}
ISR  (TIMER1_OVF_vect)
{
  TCNT1 = 3036;
  if (p == 1)
  {
    q = q + 1;
  }
//  Serial.print("q = ");Serial.println(q);
}
