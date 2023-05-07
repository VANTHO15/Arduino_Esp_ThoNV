int  QT1();
int  QT2();
int  QT3();
byte chuyenmode = 1; // 1 tay.0 lite
void setup()
{
  Serial.begin(9600);
  pinMode(4, OUTPUT); // 4 là đigital thôi
  pinMode(5, OUTPUT); // analog đk 1 động cơ
  pinMode(6, OUTPUT); // ânlog
  pinMode(7, OUTPUT); // digi
}

void loop()
{
  char data;
  int x, y, z;
 // int a=analogRead(A5);Serial.println(a);
  if (Serial.available())
  {
    data = Serial.read();
    if (data == 'H') chuyenmode = !chuyenmode;
    if (data == 'I')  Tien(255, 255);
    if (data == 'M')  Lui(255, 255);
    if (data == 'O')  Trai(255, 255);
    if (data == 'K')  Phai(255, 255);
    if (data == 'J')  Dich_phai(255, 255);
    if (data == 'P')  Dich_trai(255, 255);
    if (data == '1')  Tien(0, 0);
  }
  if (chuyenmode == 0)
  {
    if (Serial.available())
    {
      data = Serial.read();
      if (data == 'H') chuyenmode = !chuyenmode;
    }
    x = QT1();
    y = QT2();
    z = QT3();
    if ((y==1) && (x==0)&&(z==0))   Tien(200, 200);
    else if ((x==1) && (y==0)&&(z==0))  Dich_trai(200, 200);
    else if ((x==0) && (y==0)&&(z==1))   Dich_phai(200, 200);
    else if((x==1) && (y==1)&&(z==1))    Dich_trai(200, 200);
  }
}
void DCL(int chieu, int tocdo)
{
  if (chieu == 1)
  {
    digitalWrite(4, 0); // 0 tien
    analogWrite(5, tocdo);
  }
  else
  {
    digitalWrite(4, 1); //1 lui
    analogWrite(5, 255 - tocdo);
  }
}
void DCR(int chieu, int tocdo)
{
  if (chieu == 1)
  {
    digitalWrite(7, 0);
    analogWrite(6, tocdo);
  }
  else
  {
    digitalWrite(7, 1);
    analogWrite(6, 255 - tocdo);
  }
}
void Tien(int L, int R)
{
  DCR(1, R);
  DCL(1, L);
}
void Lui(int L, int R)
{
  DCR(0, R);
  DCL(0, L);
}
void Trai(int L, int R)
{
  DCR(0, R);
  DCL(1, L);
}
void Phai(int L, int R)
{
  DCR(1, R);
  DCL(0, L);
}
int  QT1()
{
  int x = analogRead(A5);
   if(x<264) return 1;
  else       return 0;
}
int  QT2()
{
  int x = analogRead(A6);
  if(x<264) return 1;
  else       return 0;
}
int  QT3()
{
  int x = analogRead(A7);
   if(x<264) return 1;
  else       return 0;
}
void Dich_trai(int L, int R)
{
  Tien(L, 0);
}
void Dich_phai(int L, int R)
{
  Tien(0, R);
}
