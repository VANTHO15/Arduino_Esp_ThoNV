#include <Wire.h>
#include   <EEPROM.h>
byte phut, giay, h, th, tphut, ts, m, n, p, ngay, thang, thu, k, gts, gtp, gth, gtthu, gtngay, gtthang, gtnam;
long nam; float ndo;
#define DS1307 0x68
void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0)  //nhap gio phu giay thì hện giờ
  {
    String data = Serial.readString();
    if (data.length() == 6)
    {
      String data1 = data.substring(0, 2);
      String data2 = data.substring(2, 4);
      String data3 = data.substring(4, 6);
      Serial.println("cap  nhap");
      m = data1.toInt();
      n = data2.toInt();
      p = data3.toInt();
      EEPROM.put(0, m);
      EEPROM.put(1, n);
      EEPROM.put(2, p);
      ts = EEPROM.read(0);
      tphut = EEPROM.read(1);
      th = EEPROM.read(2);
    }
    else if (data.length() == 14)
    {
      String data1 = data.substring(0, 2);
      String data2 = data.substring(2, 4);
      String data3 = data.substring(4, 6);
      String data4 = data.substring(6, 8);
      String data5 = data.substring(8, 10);
      String data6 = data.substring(10, 12);
      String data7 = data.substring(12, 14);
      gts = data1.toInt();
      gtp = data2.toInt();
      gth = data3.toInt();
      gtthu = data4.toInt();
      gtngay = data5.toInt();
      gtthang = data6.toInt();
      gtnam = data7.toInt();
      DS1307_setMinAndSec(gts, gtp, gth, gtthu, gtngay, gtthang, gtnam);
    }
    else  Serial.println("nhap lai ban oi!!!!");
  }
  DS1307_readMinAndSec();
  Serial.print(h); Serial.print("h  "); Serial.print(phut); Serial.print("p  "); Serial.print(giay); Serial.print("s    thu "); Serial.print(thu); Serial.print(" ngay");
  Serial.print(ngay); Serial.print(" thang"); Serial.print(thang); Serial.print(" nam "); Serial.println(nam);
  delay(1000);
}
void DS1307_readMinAndSec()
{
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0x00));
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);
  giay = bcdtodec(Wire.read() & 0x7f);
  phut = bcdtodec(Wire.read());
  h = bcdtodec(Wire.read());
  thu = bcdtodec(Wire.read());
  ngay = bcdtodec(Wire.read());
  thang = bcdtodec(Wire.read());
  nam = bcdtodec(Wire.read());
}
void DS1307_setMinAndSec(byte hr, byte mnt, byte sec, byte thu, byte day, byte date, int month)
{
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0x00));
  Wire.write(dectobcd(sec));
  Wire.write(dectobcd(mnt));
  Wire.write(dectobcd(hr));
  Wire.write(dectobcd(thu));
  Wire.write(dectobcd(day));
  Wire.write(dectobcd(date));
  Wire.write(dectobcd(month));
  Wire.endTransmission();
}
int bcdtodec(byte num)      //chuyen 16 ve 10
{
  return ((num / 16 * 10) + (num % 16));
}

int dectobcd(byte num)      //chuyen 10 ve 16
{
  return ((num / 10 * 16) + (num % 10));
}
