void Tien(int L,int R);
void DCl(int chieu,int tocdo); // chieu  =0 lui .1 tien
void DCR(int chieu,int tocdo);
void setup() 
{
  pinMode(4,OUTPUT); // 4 là đigital thôi
  pinMode(5,OUTPUT);// analog đk 1 động cơ
  pinMode(6,OUTPUT); // ânlog
  pinMode(7,OUTPUT); // digi
  Serial.begin(9600);
}
void loop()
{
  char data;
  int x,y,z;
  if (Serial.available())
  {
    data = Serial.read();
    if (data == 'M') 
    {
      Tien(150,150);
    }
     if (data == 'I')  Lui(50, 50);
    if (data == 'O')  Trai(50, 50);
    if (data == 'K')  Phai(50, 50);
    if (data == 'J')  Dich_phai(50, 50);
    if (data == 'P')  Dich_trai(50, 50);
    if (data == '1')  Tien(0, 0);
  }
}
void DCL(int chieu,int tocdo)
{
  if(chieu==1) 
            {
               digitalWrite(4,0);  // 0 tien
               analogWrite(5,tocdo);
            }
  else
           {
               digitalWrite(4,1);  //1 lui
               analogWrite(5,255-tocdo);        
           }
}
void DCR(int chieu,int tocdo)
{
  if(chieu==1) 
            {
               digitalWrite(7,0); 
               analogWrite(6,tocdo);
            }
  else
           {
               digitalWrite(7,1); 
               analogWrite(6,255-tocdo);        
           }
}
void Tien(int L,int R)
{
  DCR(1,R);
  DCL(1,L);
}
void Lui(int L, int R)
{
  DCR(0, R);
  DCL(0, L);
}
void Trai(int L, int R)
{
  DCR(1, R);
  DCL(0, L);
}
void Phai(int L, int R)
{
  DCR(0, R);
  DCL(1, L);
}
void Dich_trai(int L, int R)
{
  Tien(0, R);
}
void Dich_phai(int L, int R)
{
  Tien(L, 0);
}
