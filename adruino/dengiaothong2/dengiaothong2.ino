int a[10] = { 0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};
int dxanh = 0, ddo = 0, dvang = 0, n = 0, m = 0, l = 0;
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
  for (int i = 3; i <= 10; i++)

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
  if (Serial.available() )
  { 
    String data = Serial.readString();
    String data1 = data.substring(0, 2);
    String data2 = data.substring(2, 4);
    String data3 = data.substring(4, 6);
    int xanh = data1.toInt();
    int vang = data2.toInt();
    int doa = data3.toInt();
    while (1)
    {
      dxanh = 1;
      ddo = 0;
      dvang = 0;
      while (m <= xanh && dxanh == 1)
      { sang(xanh - m);
        digitalWrite(A0, 1);
        digitalWrite(A1, 0);
        digitalWrite(A2, 0);
      }
      dxanh = 0;
      dvang = 1;
      ddo = 0;
      while ((n <= vang) && dvang == 1)
      {
        sang(vang - n);
        digitalWrite(A0, 0);
        digitalWrite(A1, 1);
        digitalWrite(A2, 0);
      }
      dxanh = 0;
      dvang = 0;
      ddo = 1;
      while ((l <= doa) && (ddo == 1))
      {
        sang( doa - l);
        digitalWrite(A0, 0);
        digitalWrite(A1, 0);
        digitalWrite(A2, 1);
      }
      n = 0; m = 0; l = 0;
    }
  }
}
ISR  (TIMER1_OVF_vect)
{
  TCNT1 = 3036;
  
    if (dxanh == 1) m = m + 1;
    if (dvang == 1)   n = n + 1;
    if (ddo == 1) l = l + 1;

  

}
