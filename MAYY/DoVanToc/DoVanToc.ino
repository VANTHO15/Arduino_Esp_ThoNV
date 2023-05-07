#include <TimerThree.h>
#include <TimerOne.h>
#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define BtnConfig 2
#define BtnXacNhan 3
#define BtnChuyenMode 18
#define PinCongTac 20
#define Loa A8
#define Led1 A9
#define Led2 A10
#define PinChangeA 21
#define pinEN 5
#define pinPWM 6
#define CS 53
void DEM_XUNG();
void DongCo(uint8_t Chieu, uint8_t VanToc);
int i;
byte recu[3];
int valeur;
int x=0;
float pression, apxuat = 100;
uint8_t a = 0, b = 0, c = 0, d = 0, n = 0, m = 0, Lan1ChuyenMode = 0, Lan1CongTac = 0, Lan1DemXung = 0,GocQuay=70;
uint8_t Mode = 0, GiaiDoan = 1  , DemXungGD1 = 0, PWMTien = 70, ThoiGianDeLay1 = 0, PWMLui = 60, DemXungGD2 = 0, ThoiGianDeLay2 = 0;
uint8_t PWMVanToc = 50;
float HitTho = 1.2;
uint32_t NhipTho = 40, TheTich = 700;
float ChuKi, ThoiGianTho, ThoiGianhit, ThoiGianhitDC, ThoiGianThoDC, VanTocTien, VanTocLui ;
uint8_t KetThucDemXungGD1 = 0, KetThucThoiGianDeLay1 = 0, KetThucDemXungGD2 = 0, KetThucThoiGianDeLay2 = 0;
String TrangThaiHienThi = "ThongSo";
int ApXuat, VanToc, Chon = 1, BatDauChon = 1, Reset = 1, KhoiDong = 0;
uint64_t DemThoiGianDeLay1=0,DemThoiGianDeLay2=0,BatDauThoiGianDeLay1=0,BatDauThoiGianDeLay2=0,XungGD1=0,XungGD2=0;
void setup()
{
  Serial.begin(9600);
  pinMode(PinChangeA, INPUT_PULLUP);
  pinMode ( pinEN, OUTPUT ) ;
  pinMode ( pinPWM, OUTPUT ) ;
  attachInterrupt(digitalPinToInterrupt(PinChangeA), DEM_XUNG, FALLING);
  Timer3.initialize(10000);
  Timer3.attachInterrupt(Timer001s);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(Timer01s);
}

int Xung=0,Time=0;
void loop()
{
 DongCo(1,50);
}
void DEM_XUNG()
{
 
  if (Lan1DemXung == 1 )
  {
    Xung++;
  }
  Lan1DemXung = 1;
}

void DongCo(uint8_t Chieu, uint8_t TocDo)
{
  if (Chieu == 1)
  {
    digitalWrite(pinEN, 1);
    analogWrite(pinPWM, TocDo);
  }
  else
  {
    digitalWrite(pinEN, 0);
    analogWrite(pinPWM, TocDo);
  }
}
void Timer01s()
{

}
void Timer001s()
{
  Time++;
  if((Xung/(7*71.2))>=10)
  {
    Time=0;
    Xung=0;
    Serial.println(Time);
  }
}
