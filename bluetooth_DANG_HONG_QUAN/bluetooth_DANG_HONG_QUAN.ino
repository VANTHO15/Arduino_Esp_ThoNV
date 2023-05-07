void tien(int tocdo);
void  lui(int tocdo);
void setup()
{
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}
long tx = 0, ty = 0, tz = 0, a = 0;
String sx = "", sy = "", sz = "";
void loop()
{
  int i, j, k;
  if (Serial.available())
  {
    String s = Serial.readString();
    i = s.indexOf("a");
    j = s.indexOf("b");
    k = s.length();
    sx = s.substring(0, i);
    sy = s.substring(i + 1, j);
    sz = s.substring(j + 1, k - 1);
    tx = sx.toInt();
    ty = sy.toInt();
    tz = sz.toInt();
    if (tx > 50) tien(100);
    if (tx < 50) lui(100);

  }
}
void tien(int tocdo)
{
  digitalWrite(8, 1);
  analogWrite(9, 255 - tocdo);
  // digitalWrite(in3, 0);
  //  analogWrite(in4, tocdo);
}
void  lui(int tocdo)
{
  digitalWrite(8, 0);
  analogWrite(9, tocdo);
  //  digitalWrite(in3, 1);
  // analogWrite(in4, 255 - tocdo);
}
