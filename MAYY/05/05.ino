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
void FuncBtnConfig();
void FuncBtnChuyenMode();
void FuncBtnXacNhan();
void FunCongTac();
void DEM_XUNG();
void DongCo(uint8_t Chieu, uint8_t VanToc);
void  DCDungIm();
String FuncBienTro();
void Buzzer(int TrangThai);
void CamBienApXuat();
void HoatDong();
void TinhToan(uint8_t NhipTho, uint16_t TheTich, float HitTho);
void FunReset();
void HienThiLCD();
void KhoiDong();
void CanhBao();
int i;
byte recu[3];
int valeur;
int x = 0;
float pression, apxuat = 100;
uint8_t a = 0, b = 0, c = 0, d = 0, n = 0, m = 0, Lan1ChuyenMode = 0, Lan1CongTac = 0, Lan1DemXung = 0, Xung = 0, GocQuay = 70;
uint8_t Mode = 0, GiaiDoan = 0  , DemXungGD1 = 0, PWMTien = 70, ThoiGianDeLay1 = 200, PWMLui = 60, DemXungGD2 = 0, ThoiGianDeLay2 = 200;
uint8_t PWMVanToc = 50;
float HitTho = 1.2;
uint32_t NhipTho = 40, TheTich = 700;
float ChuKi, ThoiGianTho, ThoiGianhit, ThoiGianhitDC, ThoiGianThoDC, VanTocTien, VanTocLui ;
String TrangThaiHienThi = "ThongSo";
int ApXuat, VanToc, Chon = 0, BatDauChon = 1, Reset = 1, Lan1KhoiDong = 0, Lan1ReSet = 0, OnClickChuyenMode = 1, ChangeMode = 0;
uint64_t Count1 = 0, Count2 = 0, Count3 = 0, Count4 = 0, Dem1 = 0, Dem2 = 0, Dem3 = 0, Dem4 = 0,BTN=0,Lan1NutBam=0;
void setup()
{
  Serial.begin(9600);
  lcd.begin(20, 4);
  pinMode(BtnConfig, INPUT_PULLUP);
  pinMode(BtnChuyenMode, INPUT_PULLUP);
  pinMode(BtnXacNhan, INPUT_PULLUP);
  pinMode(PinCongTac, INPUT_PULLUP);
  pinMode(PinChangeA, INPUT_PULLUP);
  pinMode ( 35, OUTPUT ) ;
  pinMode ( 37, OUTPUT ) ;
  pinMode ( 39, OUTPUT ) ;
  digitalWrite(35, 0);
  digitalWrite(37, 0);
  digitalWrite(39, 0);
  pinMode ( pinEN, OUTPUT ) ;
  pinMode ( pinPWM, OUTPUT ) ;
  pinMode ( Loa, OUTPUT ) ;
  pinMode ( Led1, OUTPUT ) ;
  pinMode ( Led2, OUTPUT ) ;
  Buzzer(0);
  digitalWrite(Led1, 1);
  digitalWrite(Led2, 1);
  attachInterrupt(digitalPinToInterrupt(BtnConfig), FuncBtnConfig, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BtnChuyenMode), FuncBtnChuyenMode, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BtnXacNhan), FuncBtnXacNhan, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PinCongTac), FunCongTac, FALLING);
  attachInterrupt(digitalPinToInterrupt(PinChangeA), DEM_XUNG, FALLING);
  SPI.begin(); // initialization of SPI port
  SPI.setDataMode(SPI_MODE0); // configuration of SPI communication in mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV16); // configuration of clock at 1MHz
  pinMode(CS, OUTPUT);
  Timer3.initialize(10000);
  Timer3.attachInterrupt(Timer001s);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(Timer01s);
}
void loop()
{
  if (Lan1KhoiDong == 0)
  {
    if (Lan1ReSet == 0)
    {
      Lan1ReSet = 1;
      FunReset();
    }
    KhoiDong();
  }
  else
  {
    if (OnClickChuyenMode == 1)
    {
      OnClickChuyenMode = 0;
      FunReset();
    }
    CamBienApXuat();
    HienThiLCD();
    TinhToan( NhipTho,  TheTich,  HitTho);
    CanhBao();
    HoatDong();
  }

}
void KhoiDong()
{

  lcd.setCursor(0, 0);
  lcd.print("     Chon Mode !" );
  if (Chon == 0 )
  {
    lcd.setCursor(0, 1);
    lcd.print(">>> Mode Ho Tro ");
    lcd.setCursor(0, 2);
    lcd.print("    Mode Tro Tho ");
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("    Mode Ho Tro ");
    lcd.setCursor(0, 2);
    lcd.print(">>> Mode Tro Tho ");
  }
}
void HoatDong()
{
  if (Mode == 1)
  {
    digitalWrite(Led2, 1);
    digitalWrite(Led1, 0);
    switch (GiaiDoan)
    {
      case 1:
        {
          Dem1 = 1;
          DongCo(1, 40); //PWMTien
          break;
        }
      case 2:
        {
          Dem2 = 1;
          DCDungIm();
          break;
        }
      case 3:
        {
          Dem3 = 1;
          DongCo(0, 40 ); // PWMLui
          break;
        }
      case 4:
        {
          Dem4 = 1;
          DCDungIm();
          break;
        }
    }
  }
  else if (Mode == 2)
  {
    digitalWrite(Led2, 0);
    digitalWrite(Led1, 1);
    if (ApXuat > 0)
    {
      DongCo(1, 50 ); //PWMVanToc
    }
    else
    {
      DongCo(0, 50 ); // PWMVanToc
    }
  }
}
void FuncBtnConfig()
{
  TrangThaiHienThi = "ConFig";
  digitalWrite(35, !digitalRead(35));
  a++;
}

void FuncBtnXacNhan()
{

  Buzzer(0);
  String Str = FuncBienTro();
  String BT1 = Str.substring(Str.indexOf("a") + 1, Str.indexOf("b"));
  String BT2 = Str.substring(Str.indexOf("b") + 1, Str.indexOf("c"));
  String BT3 = Str.substring(Str.indexOf("c") + 1, Str.indexOf("d"));
  String BT4 = Str.substring(Str.indexOf("d") + 1, Str.indexOf("e"));
  String BT5 = Str.substring(Str.indexOf("e") + 1, Str.indexOf("f"));
  digitalWrite(37, !digitalRead(37));
  b++;
  if ( (TrangThaiHienThi == "ConFig") && (b > 2))
  {
    ApXuat = apxuat;
    HitTho = BT1.toFloat();
    NhipTho = BT2.toInt();
    TheTich = BT3.toInt();
    VanToc = BT4.toInt();
    TrangThaiHienThi = "ThongSo";
  }
  if (Lan1KhoiDong == 0)
  {
    Lan1KhoiDong = 1;
    TrangThaiHienThi = "ConFig";
    if (Chon == 0)
    {
      Mode = 1;
    }
    else
    {
      Mode = 2;
    }
    GiaiDoan = 1;
  }

}
void FuncBtnChuyenMode()
{

  Chon = !Chon;
  c++;
  if (Mode == 1)
  {
    Mode = 2;
  }
  else if (Mode == 2)
  {
    Mode = 1;
  }
  if (Lan1KhoiDong != 0)
  {
    ChangeMode = 1;
  }
  TrangThaiHienThi = "ConFig";
  digitalWrite(39, !digitalRead(39));
}

void FunCongTac()
{
  d++;
  if (Lan1CongTac != 0)
  {
    Reset = 0;
    if(Lan1NutBam!=0)
    {
      BTN=1;
    }
    Lan1NutBam=1;
  }
  Lan1CongTac = 1;
}

void DEM_XUNG()
{
  x++;
  if (Lan1DemXung == 1 )
  {

  }
  Lan1DemXung = 1;
}
void CanhBao()
{
  if (Mode == 1)
  {
    if (ApXuat > 1000)
    {
      Buzzer(1);
    }
  }
  else if (Mode == 2)
  {
    if (ApXuat > 1000)
    {
      Buzzer(1);
    }
  }

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
String FuncBienTro()
{
  int BT1 = analogRead(A2);
  int BT2 = analogRead(A3);
  int BT3 = analogRead(A4);
  int BT4 = analogRead(A5);
  int BT5 = analogRead(A6);
  BT1 = map(BT1, 0, 1023, 0, 150);  // hit tho
  BT2 = map(BT2, 0, 1023, 20, 40); // nhip tho
  BT3 = map(BT3, 0, 1023, 0, 1000); // the tich
  BT4 = map(BT4, 0, 1023, 10, 30 ); // van  toc
  BT5 = map(BT5, 0, 1023, 0, 100); // Do Nhay
  float BT = BT1 / 100.0;
  String Dulieu = "a" + String(BT) + "b" + String(BT2) + "c" + String(BT3) + "d" + String(BT4) + "e"
                  + String(BT5) + "f";
  Serial.println(Dulieu);
  return Dulieu;
}
void Buzzer(int TrangThai)
{
  digitalWrite(Loa, !TrangThai);
}
void CamBienApXuat()
{
  digitalWrite(CS, LOW); // activation of CS line
  delayMicroseconds(20);
  for (i = 0; i < 2; i = i + 1)
  {
    recu[i] = SPI.transfer(0); // Sending 2 data to retrieve the value of the two -byte conversion
    delayMicroseconds(20);
  }
  digitalWrite(CS, HIGH); // deactivation of CS line
  valeur = (recu[0] << 8 | recu[1]);
  pression = (valeur / 4096.0 - 0.08) / 0.09; // The form given by the documentation
  float numerator = (2 * (pression)) / 1.128 ;
  float velocity = (numerator) * 0.5;
  apxuat = pression ;
  Serial.println(pression);
}
void TinhToan(uint8_t NhipTho, uint16_t TheTich, float HitTho)
{
  ChuKi = 60.0 / NhipTho;
  ThoiGianTho = ChuKi / float(1 + HitTho);
  ThoiGianhit = ChuKi - ThoiGianTho;
  ThoiGianTho=ThoiGianTho*1000;
  ThoiGianhit=ThoiGianhit*1000;
  ThoiGianhitDC = ThoiGianhit - ThoiGianDeLay1;
  ThoiGianThoDC = ThoiGianTho - ThoiGianDeLay2;
  GocQuay = map(TheTich, 0, 1000, 0, 180); // thể tích từ 0->1000 => Goc
  VanTocTien = (GocQuay / 360.0) * (60.0*1000 / ThoiGianhitDC);
  VanTocLui = (GocQuay / 360.0) * (60.0*1000 / ThoiGianThoDC);
  PWMTien = 60  ;//VanTocTien;
  PWMLui =  50  ;//VanTocLui;
  PWMVanToc = 60  ; //VanToc;
  Serial.println(String(GocQuay)+" "+ String(VanTocTien)+" "+ String(VanTocLui));
}
void  DCDungIm()
{
  digitalWrite(pinEN, 0);
  digitalWrite(pinPWM, 0);
}
void FunReset()
{
  while (Reset == 1)
  {
    DongCo(1, 50);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("   RESETTING... " );
  }
  DCDungIm();
  Reset = 1;
}
void HienThiLCD()
{
  String Str = FuncBienTro();
  String BT1 = Str.substring(Str.indexOf("a") + 1, Str.indexOf("b"));
  String BT2 = Str.substring(Str.indexOf("b") + 1, Str.indexOf("c"));
  String BT3 = Str.substring(Str.indexOf("c") + 1, Str.indexOf("d"));
  String BT4 = Str.substring(Str.indexOf("d") + 1, Str.indexOf("e"));
  String BT5 = Str.substring(Str.indexOf("e") + 1, Str.indexOf("f"));
  if (Mode == 1)
  {
    if (ChangeMode == 1)
    {
      ChangeMode = 0;
      FunReset();
    }
    if (TrangThaiHienThi == "ConFig")
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   Set Ep Tho " );
      lcd.setCursor(0, 1);
      lcd.print("Nhip Tho : " + String(BT2) + " L/P");
      lcd.setCursor(0, 2);
      lcd.print("TheTich  : " + String(BT3) + " Cm3" );
      lcd.setCursor(0, 3);
      lcd.print("Hit Tho  : " + String(BT1)  );
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("      Ep Tho " );
      lcd.setCursor(0, 1);
      lcd.print("Nhip Tho: " + String(NhipTho) + " L/P");
      lcd.setCursor(0, 2);
      lcd.print("The Tich: " + String(TheTich) + " Cm3" );
      lcd.setCursor(0, 3);
      lcd.print("Hit Tho : " + String(HitTho) );
    }
  }
  if (Mode == 2)
  {
    if (ChangeMode == 1)
    {
      ChangeMode = 0;
      FunReset();
    }
    if (TrangThaiHienThi == "ConFig")
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   Set Tro Tho !" );
      lcd.setCursor(0, 2);
      lcd.print(" Van Toc : " + String(BT4) + " V/P" );

    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("     Tro Tho !" );
      lcd.setCursor(0, 1);
      lcd.print(" Van Toc : " + String(VanToc) + " V/P" );
      lcd.setCursor(0, 2);
      lcd.print(" Ap Xuat : " + String(apxuat) + " V/P" );
    }
  }
}

void Timer01s()
{

}

void Timer001s()
{
  if (Dem1 == 1)
  {
    Count1++;
  }
  if (Dem2 == 1)
  {
    Count2++;
  }
  if (Dem3 == 1)
  {
    Count3++;
  }
  if (Dem4 == 1)
  {
    Count4++;
  }
  ////////////////////////////////////
  if (Count1 >= (ThoiGianhitDC/10))
  {
    GiaiDoan = 2;
    Count1 = 0;
    Dem1 = 0;
  }
  if (Count2 >= (ThoiGianDeLay1/10))
  {
    GiaiDoan = 3;
    Count2 = 0;
    Dem2 = 0;
  }
  if (Count3 >= (ThoiGianThoDC/10))
  {
    GiaiDoan = 4;
    Count3 = 0;
    Dem3 = 0;
  }
  if ((Count4 >= (ThoiGianDeLay2/10))&&(BTN==1) )
  {
    BTN=0;
    GiaiDoan = 1;
    Count4 = 0;
    Dem4 = 0;
  }
}
