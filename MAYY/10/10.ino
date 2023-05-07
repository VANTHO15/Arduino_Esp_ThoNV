#include <TimerThree.h>
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
volatile float pression, apxuat = 100, DoNhay = 0.05;
volatile uint8_t a = 0, b = 0, c = 0, d = 0, n = 0, m = 0, Lan1ChuyenMode = 0, Lan1CongTac = 0, Lan1DemXung = 0, Xung = 0, GocQuay = 70;
volatile uint8_t Mode = 0, GiaiDoan = 0  , DemXungGD1 = 0, PWMTien = 70, ThoiGianDeLay1 = 200, PWMLui = 60, DemXungGD2 = 0, ThoiGianDeLay2 = 200;
volatile uint8_t PWMVanToc = 50;
volatile float HitTho = 1.2;
volatile uint32_t NhipTho = 40, TheTich = 700;
volatile float ChuKi, ThoiGianTho, ThoiGianhit, ThoiGianhitDC, ThoiGianThoDC, VanTocTien, VanTocLui ;
volatile String TrangThaiHienThi = "ThongSo";
volatile int ApXuat, VanToc, Chon = 0, BatDauChon = 1, Reset = 1, Lan1KhoiDong = 0, Lan1ReSet = 0, OnClickChuyenMode = 1, ChangeMode = 0;
volatile uint64_t Count1 = 0, Count2 = 0, Count3 = 0, Count4 = 0, Dem1 = 0, Dem2 = 0, Dem3 = 0, Dem4 = 0, BTN = 0, Lan1NutBam = 0;
volatile int Click = 0,Enter=0;
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

}
void loop()
{
  if (Lan1KhoiDong == 0)
  {
    FunReset();
    KhoiDong();
  }
  else
  {
    FunReset();
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
  if (Mode == 1 && (Enter==1))
  {
    digitalWrite(Led2, 1);
    digitalWrite(Led1, 0);
    if (GiaiDoan == 1)
    {
      DongCo(1, PWMTien);
    }
    else
    {
      DongCo(0, PWMLui);
    }
  }
  else if (Mode == 2)
  {
    Serial.println(apxuat);
    digitalWrite(Led2, 0);
    digitalWrite(Led1, 1);
    if (apxuat <= (-0.1))//DoNhay
    {
      DongCo(1, 90 ); //PWMVanToc
      Click = 0;
    }
    else {
      if (Click == 1)
      {
        DCDungIm(); // PWMVanToc
      }
      else
      {
        DongCo(0, 40);
      }
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
    Enter=1;
    ApXuat = apxuat;
    float bT1 = BT1.toFloat();
    if ((bT1 >= 0) && (bT1 < 70))
    {
      HitTho = 1;
    }
    else if ((bT1 >= 140) && (bT1 < 210))
    {
      HitTho = 1 / 1.2;
    }
    else if ((bT1 >= 210) && (bT1 < 280))
    {
      HitTho = 1 / 1.4;
    }
    else if ((bT1 >= 280) && (bT1 < 350))
    {
      HitTho = 1 / 1.6;
    }
    else if ((bT1 >= 350) && (bT1 < 420))
    {
      HitTho = 1 / 1.8;
    }
    else if ((bT1 >= 420) && (bT1 < 490))
    {
      HitTho = 1 / 2.0;
    }
    else if ((bT1 >= 490) && (bT1 < 560))
    {
      HitTho = 1 / 2.2;
    }
    else if ((bT1 >= 560) && (bT1 < 630))
    {
      HitTho = 1 / 2.4;
    }
    else if ((bT1 >= 630) && (bT1 < 700))
    {
      HitTho = 1 / 2.6;
    }
    else if ((bT1 >= 700) && (bT1 < 770))
    {
      HitTho = 1 / 2.8;
    }
    else if ((bT1 >= 770) && (bT1 < 840))
    {
      HitTho = 1 / 3.0;
    }
    else if ((bT1 >= 840) && (bT1 < 910))
    {
      HitTho = 1 / 3.2;
    }
    else if ((bT1 >= 910) && (bT1 < 980))
    {
      HitTho = 1 / 3.4;
    }
    else if ((bT1 >= 980) && (bT1 < 1000))
    {
      HitTho = 1 / 3.6;
    }
    else if ((bT1 >= 1000) && (bT1 < 1010))
    {
      HitTho = 1 / 3.8;
    }
    else if ((bT1 >= 1010) && (bT1 <= 1023))
    {
      HitTho = 1 / 4.0;
    }
    NhipTho = BT2.toInt();
    TheTich = BT3.toInt();
    VanToc = BT4.toInt();
    DoNhay = BT5.toFloat();
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
  Enter=0;
  if (Lan1KhoiDong != 0)
  {
    Reset = 1;
  }
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
  TrangThaiHienThi = "ConFig";
  digitalWrite(39, !digitalRead(39));
}

void FunCongTac()
{
  d++;
  if (Lan1CongTac != 0)
  {
    if (Reset == 1)
    {
      DCDungIm();
    }
    Reset = 0;
    if (Lan1NutBam != 0)
    {
      BTN = 1;
    }
    Lan1NutBam = 1;
    Click = 1;
  }
  Lan1CongTac = 1;
}

void DEM_XUNG()
{

  if (Lan1DemXung == 1 )
  {
    if (GiaiDoan == 1)
    {

    }
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
    if (VanToc > 20)
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
  float BT5 = analogRead(A6);
  String bt1 = "1/1";
  if ((BT1 >= 0) && (BT1 < 70))
  {
    bt1 = "1/1";
  }
  else if ((BT1 >= 140) && (BT1 < 210))
  {
    bt1 = "1/1.2";
  }
  else if ((BT1 >= 210) && (BT1 < 280))
  {
    bt1 = "1/1.4";
  }
  else if ((BT1 >= 280) && (BT1 < 350))
  {
    bt1 = "1/1.6";
  }
  else if ((BT1 >= 350) && (BT1 < 420))
  {
    bt1 = "1/1.8";
  }
  else if ((BT1 >= 420) && (BT1 < 490))
  {
    bt1 = "1/2";
  }
  else if ((BT1 >= 490) && (BT1 < 560))
  {
    bt1 = "1/2.2";
  }
  else if ((BT1 >= 560) && (BT1 < 630))
  {
    bt1 = "1/2.4";
  }
  else if ((BT1 >= 630) && (BT1 < 700))
  {
    bt1 = "1/2.6";
  }
  else if ((BT1 >= 700) && (BT1 < 770))
  {
    bt1 = "1/2.8";
  }
  else if ((BT1 >= 770) && (BT1 < 840))
  {
    bt1 = "1/3";
  }
  else if ((BT1 >= 840) && (BT1 < 910))
  {
    bt1 = "1/3.2";
  }
  else if ((BT1 >= 910) && (BT1 < 980))
  {
    bt1 = "1/3.4";
  }
  else if ((BT1 >= 980) && (BT1 < 1000))
  {
    bt1 = "1/3.6";
  }
  else if ((BT1 >= 1000) && (BT1 < 1010))
  {
    bt1 = "1/3.8";
  }
  else if ((BT1 >= 1010) && (BT1 <= 1023))
  {
    bt1 = "1/4";
  }
  //BT1 = map(BT1, 0, 1023, 0, 150);  // hit tho
  BT2 = map(BT2, 0, 1023, 20, 40); // nhip tho
  BT3 = map(BT3, 0, 1023, 0, 1000); // the tich
  BT4 = map(BT4, 0, 1023, 10, 30 ); // van  toc
  //BT5 = map(BT5, 0, 1023, 0, 5); // Do Nhay
  BT5 = BT5 * 0.5 / 1023;
  float BT = BT1 / 100.0;
  String Dulieu = "a" + String(BT1) + "b" + String(BT2) + "c" + String(BT3) + "d" + String(BT4) + "e"
                  + String(BT5) + "f" + bt1 + "g";
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
  ThoiGianTho = ThoiGianTho * 1000;
  ThoiGianhit = ThoiGianhit * 1000;
  ThoiGianhitDC = ThoiGianhit ;
  ThoiGianThoDC = ThoiGianTho ;
  GocQuay = map(TheTich, 0, 1000, 0, 180); // thể tích từ 0->1000 => Goc
  VanTocTien = (GocQuay / 360.0) * (60.0 * 1000 / ThoiGianhitDC);
  VanTocLui = (GocQuay / 360.0) * (60.0 * 1000 / ThoiGianThoDC);
  PWMTien = 80  ;//VanTocTien;
  PWMLui =  60  ;//VanTocLui;
  PWMVanToc = 60  ; //VanToc;
 // Serial.println(String(GocQuay) + " " + String(VanTocTien) + " " + String(VanTocLui));
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
}
void HienThiLCD()
{
  String Str = FuncBienTro();
  String BT1 = Str.substring(Str.indexOf("a") + 1, Str.indexOf("b"));
  String BT2 = Str.substring(Str.indexOf("b") + 1, Str.indexOf("c"));
  String BT3 = Str.substring(Str.indexOf("c") + 1, Str.indexOf("d"));
  String BT4 = Str.substring(Str.indexOf("d") + 1, Str.indexOf("e"));
  String BT5 = Str.substring(Str.indexOf("e") + 1, Str.indexOf("f"));
  String bt1 = Str.substring(Str.indexOf("f") + 1, Str.indexOf("g"));
  if (Mode == 1)
  {
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
      lcd.print("Hit Tho  : " + bt1 );
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
    if (TrangThaiHienThi == "ConFig")
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   Set Tro Tho !" );
      lcd.setCursor(0, 2);
      lcd.print(" Van Toc : " + String(BT4) + " V/P" );
      lcd.setCursor(0, 3);
      lcd.print(" Do Nhay: " + String(BT5) + "CmH20" );
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
      lcd.setCursor(0, 3);
      lcd.print(" Do Nhay : " + String(DoNhay) + "CmH" );

    }
  }
}
void Timer001s()
{
  if (GiaiDoan == 1)
  {
    x++;
    if (x >= (70))
    {
      GiaiDoan = 2;
      x = 0;
      BTN = 0;
    }
  }
  if (BTN == 1)
  {
    GiaiDoan = 1;
  }
}
