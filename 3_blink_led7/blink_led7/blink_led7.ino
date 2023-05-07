int a[10] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
void hienthi(int n)
{
  int x = a[n];
  int kiemtra = 0;
  for (int i = 1; i <= 12; i++)
  {
    if ((i == 6) || (i == 7) || (i == 8) || (i == 11)) kiemtra = 1;
    if (kiemtra == 0)
    {
      digitalWrite(i, x & 0x01);
      x = x >> 1;
    }
    int kiemtra = 0;
  }
}
void  sang(int n)
{    
     int hc=n/10;
     int dv=n%10;
     digitalWrite(14,1);
     digitalWrite(13,0);
     hienthi(hc);
     delay(10);
     digitalWrite(13,1);
     digitalWrite(14,0);
     hienthi(dv);
     delay(10);
}
void setup()
{
//  pinMode(0, OUTPUT); 
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(16, INPUT_PULLUP);
}

void loop()
{

  sang(7);

}
