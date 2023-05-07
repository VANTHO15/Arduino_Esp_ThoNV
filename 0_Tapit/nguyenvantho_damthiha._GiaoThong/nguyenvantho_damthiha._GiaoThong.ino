int a[10] = { 0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};
int dxanh = 0, ddo = 0, dvang = 0, n = 0, m = 0, l = 0;
int txanh = 20;
int tvang = 03;
int tdo   = 10;
void  hienthi(int n)
{
  int x = a[n];
  for (int i = 3; i <= 10; i++)
  {
    digitalWrite(i, x & 0x01);
    x = x >> 1;
  }
}
void quetled(int a)
{
  digitalWrite(11, 1);
  digitalWrite(12, 0);
  hienthi(a / 10);
  delay(10);
  digitalWrite(12, 1);
  digitalWrite(11, 0);
  hienthi(a % 10);
  delay(10);
}
void setup()
{
  for (int i = 3; i <= 12; i++)
  { 
    pinMode(i, OUTPUT);
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
  dxanh = 1;
}

void loop()
{
  if (Serial.available() > 0)
  { 
    String data = Serial.readString();
    String data1 = data.substring(0, 2);
    String data2 = data.substring(2, 4);
    String data3 = data.substring(4, 6);
    txanh = data1.toInt();
    tvang = data2.toInt();
    tdo   = data3.toInt();
  }  
 if(dxanh == 1)
  {
    if(m <= txanh) 
      {
        quetled(txanh - m);
        digitalWrite(A0, 1);
        digitalWrite(A1, 0);
        digitalWrite(A2, 0);
      }
    else
     {
        dxanh = 0;
        dvang = 1;
        ddo = 0;
     }
  } 
   else if (dvang ==1)
    {  
      if(n <= tvang)
         {
            quetled(tvang - n);
            digitalWrite(A0, 0);
            digitalWrite(A1, 1);
            digitalWrite(A2, 0);
          }
       else
         {
          dxanh = 0;
          dvang = 0;
          ddo = 1;
         }
    }
    else if (ddo == 1)
     { 
      if (l <= tdo)
      {
        quetled(tdo - l);
        digitalWrite(A0, 0);
        digitalWrite(A1, 0);
        digitalWrite(A2, 1);
      }
      else 
      {
        dxanh = 1;
        dvang = 0;
        ddo = 0;
        n = 0; m = 0; l = 0;
      }
    }
}
ISR (TIMER1_OVF_vect)
{
    TCNT1 = 3036;
    if (dxanh == 1) m = m + 1;
    if (dvang == 1)   n = n + 1;
    if (ddo == 1) l = l + 1;
}
