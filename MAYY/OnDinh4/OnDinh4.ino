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
volatile float pression, apxuat = 100 ;
volatile uint8_t a = 0, b = 0, c = 0, d = 0, n = 0, m = 0, Lan1ChuyenMode = 0, Lan1CongTac = 0, Lan1DemXung = 0, Xung = 0, GocQuay = 70;
volatile uint8_t Mode = 0, GiaiDoan = 0  , DemXungGD1 = 0, PWMTien = 70, ThoiGianDeLay1 = 200, PWMLui = 60, DemXungGD2 = 0, ThoiGianDeLay2 = 200;
volatile uint8_t PWMVanToc = 50;
volatile float HitTho = 1.2;
volatile uint32_t NhipTho = 40, TheTich = 700;
volatile float ChuKi, ThoiGianTho, ThoiGianhit, ThoiGianhitDC, ThoiGianThoDC, VanTocTien, VanTocLui ;
volatile String TrangThaiHienThi = "ThongSo", GiaTri = "Duong";
volatile int ApXuat, VanToc, Chon = 0, BatDauChon = 1, Reset = 1, Lan1KhoiDong = 0, Lan1ReSet = 0, OnClickChuyenMode = 1, ChangeMode = 0;
volatile uint64_t Count1 = 0, Count2 = 0, Count3 = 0, Count4 = 0, Dem1 = 0, Dem2 = 0, Dem3 = 0, Dem4 = 0, BTN = 0, Lan1NutBam = 0, DemCanhBao1 = 0, CanhBao1 = 0;
volatile int Click = 0, Enter = 0, lan1Tho = 0, Xoa = 0, DoNhay = -1;
uint64_t t=100,Delay=0,Tang=0;
int ARRvao[100] = {55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 55, 56, 56, 57, 58, 58, 60, 60, 61, 61, 62, 62, 63, 63, 64, 66, 67, 67, 68, 68, 69, 70, 71, 72,
                   73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 86, 87, 88, 89, 91, 92, 93, 94, 95, 96, 97, 98, 100
                  };
int ARRra[200] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
                  50, 50, 50, 50, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
                  55, 56, 84, 57, 86, 58, 59, 89, 60, 61, 62, 64, 94, 65, 66, 67, 69, 70, 71, 72, 73, 103, 75, 77, 79, 81, 83, 85, 87, 90, 91, 93, 96, 98, 100
                  , 100, 100, 100, 100, 100, 100, 100, 100, 100, 100
                 } ;
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
  if (Xoa == 1)
  {
    lcd.clear();
    Xoa = 0;
  }
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
  lcd.print("        MODE !" );
  if (Chon == 0 )
  {
    lcd.setCursor(0, 1);
    lcd.print(">>> Mode Control ");
    lcd.setCursor(0, 2);
    lcd.print("    Mode Support ");
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("    Mode Control ");
    lcd.setCursor(0, 2);
    lcd.print(">>> Mode Support ");
  }
}
void HoatDong()
{
  if (Mode == 1 && (Enter == 1))
  {
    Buzzer(0);
    DemCanhBao1 = 0;
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
    if (lan1Tho == 1)
    {
      CanhBao1 = 1;
    }
    Serial.println(apxuat);
    digitalWrite(Led2, 0);
    digitalWrite(Led1, 1);

    if (apxuat <= (DoNhay) )//
    {
      if (Click == 1)
      {
        CanhBao1 = 0;
        lan1Tho = 1;
        DemCanhBao1 = 0;
        DongCo(1, PWMVanToc ); //PWMVanToc   80
        Click = 0;
      }

    }
    else {
      lan1Tho = 0;
      if (Click == 1)
      {
        DCDungIm(); // PWMVanToc
      }
      else
      {
        DongCo(0, 50);  //50
      }
    }
  }
}
void FuncBtnConfig()
{
  Xoa = 1;
  TrangThaiHienThi = "ConFig";
  digitalWrite(35, !digitalRead(35));
  a++;
}
void FuncBtnXacNhan()
{
  Xoa = 1;
  Buzzer(0);
  DemCanhBao1 = 0;
  CanhBao1 = 0;
  String Str = FuncBienTro();
  String BT1 = Str.substring(Str.indexOf("a") + 1, Str.indexOf("b"));
  String BT2 = Str.substring(Str.indexOf("b") + 1, Str.indexOf("c"));
  String BT3 = Str.substring(Str.indexOf("c") + 1, Str.indexOf("d"));
  String BT4 = Str.substring(Str.indexOf("d") + 1, Str.indexOf("e"));
  String BT5 = Str.substring(Str.indexOf("e") + 1, Str.indexOf("f"));
  digitalWrite(37, !digitalRead(37));
  b++;
  if ( (TrangThaiHienThi == "ConFig") && (b > 1))
  {
    Enter = 1;
    ApXuat = apxuat;

    if (BT1 == "1/1.0")
    {
      HitTho = 1 / 1.0;
    }
    else if (BT1 == "1/1.2")
    {
      HitTho = 1 / 1.2;
    }
    else if (BT1 == "1/1.4")
    {
      HitTho = 1 / 1.4;
    }
    else if (BT1 == "1/1.6")
    {
      HitTho = 1 / 1.6;
    }
    else if (BT1 == "1/1.8")
    {
      HitTho = 1 / 1.8;
    }
    else if (BT1 == "1/2.0")
    {
      HitTho = 1 / 2.0;
    }
    else if (BT1 == "1/2.2")
    {
      HitTho = 1 / 2.2;
    }
    else if (BT1 == "1/2.4")
    {
      HitTho = 1 / 2.4;
    }
    else if (BT1 == "1/2.6")
    {
      HitTho = 1 / 2.6;
    }
    else if (BT1 == "1/2.8")
    {
      HitTho = 1 / 2.8;
    }
    else if (BT1 == "1/3.0")
    {
      HitTho = 1 / 3.0;
    }
    else if (BT1 == "1/3.2")
    {
      HitTho = 1 / 3.2;
    }
    else if (BT1 == "1/3.4")
    {
      HitTho = 1 / 3.4;
    }
    else if (BT1 == "1/3.6")
    {
      HitTho = 1 / 3.6;
    }
    else if (BT1 == "1/3.8")
    {
      HitTho = 1 / 3.8;
    }
    else if (BT1 == "1/4.0")
    {
      HitTho = 1 / 4.0;
    }
    NhipTho = BT2.toInt();
    TheTich = BT3.toInt();
    VanToc = BT4.toInt();
    PWMVanToc = map(VanToc, 0, 30, 50, 108);
    DoNhay = BT5.toInt();
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
  Xoa = 1;
  Enter = 0;
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
    Delay=1;
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
  //  if (Mode == 1)
  //  {
  //    if (ApXuat > 1000)
  //    {
  //      Buzzer(1);
  //    }
  //  }
  //  else if (Mode == 2)
  //  {
  ////    if (VanToc > 20)
  ////    {
  ////      Buzzer(1);
  ////    }
  //  }

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
  long BT1 = analogRead(A2);
  long BT2 = analogRead(A3);
  long BT3 = analogRead(A4);
  long BT4 = analogRead(A5);
  long BT5 = analogRead(A6);
  String bt1 = "1/1.0";
  if ((BT1 >= 0) && (BT1 < 64))
  {
    bt1 = "1/1.0";
  }
  else if ((BT1 >= 64) && (BT1 < 128))
  {
    bt1 = "1/1.2";
  }
  else if ((BT1 >= 128) && (BT1 < 192))
  {
    bt1 = "1/1.4";
  }
  else if ((BT1 >= 192) && (BT1 < 256))
  {
    bt1 = "1/1.6";
  }
  else if ((BT1 >= 256) && (BT1 < 320))
  {
    bt1 = "1/1.8";
  }
  else if ((BT1 >= 320) && (BT1 < 384))
  {
    bt1 = "1/2.0";
  }
  else if ((BT1 >= 384) && (BT1 < 448))
  {
    bt1 = "1/2.2";
  }
  else if ((BT1 >= 448) && (BT1 < 512))
  {
    bt1 = "1/2.4";
  }
  else if ((BT1 >= 512) && (BT1 < 576))
  {
    bt1 = "1/2.6";
  }
  else if ((BT1 >= 576) && (BT1 < 640))
  {
    bt1 = "1/2.8";
  }
  else if ((BT1 >= 640) && (BT1 < 704))
  {
    bt1 = "1/3.0";
  }
  else if ((BT1 >= 704) && (BT1 < 768))
  {
    bt1 = "1/3.2";
  }
  else if ((BT1 >= 768) && (BT1 < 832))
  {
    bt1 = "1/3.4";
  }
  else if ((BT1 >= 832) && (BT1 < 896))
  {
    bt1 = "1/3.6";
  }
  else if ((BT1 >= 896) && (BT1 < 960))
  {
    bt1 = "1/3.8";
  }
  else if ((BT1 >= 960) && (BT1 <= 1023))
  {
    bt1 = "1/4.0";
  }
  /////////////The tich/////////////
  if (BT3 < 17)
  {
    BT3 = 200;
  }
  else if ((BT3 >= 17) && (BT3 < 34))
  {
    BT3 = 210;
  }
  else if ((BT3 >= 34) && (BT3 < 51))
  {
    BT3 = 220;
  }
  else if ((BT3 >= 51) && (BT3 < 68))
  {
    BT3 = 230;
  }
  else if ((BT3 >= 68) && (BT3 < 85))
  {
    BT3 = 240;
  }
  else if ((BT3 >= 85) && (BT3 < 102))
  {
    BT3 = 250;
  }
  else if ((BT3 >= 102) && (BT3 < 119))
  {
    BT3 = 260;
  }
  else if ((BT3 >= 119) && (BT3 < 136))
  {
    BT3 = 270;
  }
  else if ((BT3 >= 136) && (BT3 < 153))
  {
    BT3 = 280;
  }
  else if ((BT3 >= 153) && (BT3 < 170))
  {
    BT3 = 290;
  }
  else if ((BT3 >= 170) && (BT3 < 187))
  {
    BT3 = 300;
  }
  else if ((BT3 >= 187) && (BT3 < 204))
  {
    BT3 = 310;
  }
  else if ((BT3 >= 204) && (BT3 < 221))
  {
    BT3 = 320;
  }
  else if ((BT3 >= 238) && (BT3 < 255))
  {
    BT3 = 330;
  }
  else if ((BT3 >= 255) && (BT3 < 272))
  {
    BT3 = 340;
  }
  else if ((BT3 >= 272) && (BT3 < 289))
  {
    BT3 = 350;
  }
  else if ((BT3 >= 289) && (BT3 < 306))
  {
    BT3 = 360;
  }
  else if ((BT3 >= 306) && (BT3 < 323))
  {
    BT3 = 370;
  }
  else if ((BT3 >= 323) && (BT3 < 340))
  {
    BT3 = 380;
  }
  else if ((BT3 >= 340) && (BT3 < 357))
  {
    BT3 = 390;
  }
  else if ((BT3 >= 357) && (BT3 < 374))
  {
    BT3 = 400;
  }
  else if ((BT3 >= 374) && (BT3 < 391))
  {
    BT3 = 410;
  }
  else if ((BT3 >= 391) && (BT3 < 408))
  {
    BT3 = 420;
  }
  else if ((BT3 >= 408) && (BT3 < 425))
  {
    BT3 = 430;
  }
  else if ((BT3 >= 425) && (BT3 < 442))
  {
    BT3 = 440;
  }
  else if ((BT3 >= 442) && (BT3 < 459))
  {
    BT3 = 450;
  }
  else if ((BT3 >= 459) && (BT3 < 476))
  {
    BT3 = 460;
  }
  else if ((BT3 >= 476) && (BT3 < 493))
  {
    BT3 = 470;
  }
  else if ((BT3 >= 493) && (BT3 < 510))
  {
    BT3 = 480;
  }
  else if ((BT3 >= 510) && (BT3 < 527))
  {
    BT3 = 490;
  }
  else if ((BT3 >= 527) && (BT3 < 544))
  {
    BT3 = 500;
  }
  else if ((BT3 >= 544) && (BT3 < 561))
  {
    BT3 = 510;
  }
  else if ((BT3 >= 561) && (BT3 < 578))
  {
    BT3 = 520;
  }
  else if ((BT3 >= 578) && (BT3 < 595))
  {
    BT3 = 530;
  }
  else if ((BT3 >= 595) && (BT3 < 612))
  {
    BT3 = 540;
  }
  else if ((BT3 >= 612) && (BT3 < 629))
  {
    BT3 = 550;
  }
  else if ((BT3 >= 629) && (BT3 < 646))
  {
    BT3 = 560;
  }
  else if ((BT3 >= 646) && (BT3 < 663))
  {
    BT3 = 570;
  }
  else if ((BT3 >= 663) && (BT3 < 680))
  {
    BT3 = 580;
  }
  else if ((BT3 >= 680) && (BT3 < 697))
  {
    BT3 = 590;
  }
  else if ((BT3 >= 697) && (BT3 < 714))
  {
    BT3 = 600;
  }
  else if ((BT3 >= 714) && (BT3 < 731))
  {
    BT3 = 610;
  }
  else if ((BT3 >= 731) && (BT3 < 748))
  {
    BT3 = 620;
  }
  else if ((BT3 >= 748) && (BT3 < 765))
  {
    BT3 = 630;
  }
  else if ((BT3 >= 765) && (BT3 < 782))
  {
    BT3 = 640;
  }
  else if ((BT3 >= 782) && (BT3 < 799))
  {
    BT3 = 650;
  }
  else if ((BT3 >= 799) && (BT3 < 816))
  {
    BT3 = 660;
  }
  else if ((BT3 >= 816) && (BT3 < 833))
  {
    BT3 = 670;
  }
  else if ((BT3 >= 833) && (BT3 < 850))
  {
    BT3 = 680;
  }
  else if ((BT3 >= 850) && (BT3 < 867))
  {
    BT3 = 690;
  }
  else if ((BT3 >= 867) && (BT3 < 884))
  {
    BT3 = 700;
  }
  else if ((BT3 >= 884) && (BT3 < 901))
  {
    BT3 = 710;
  }
  else if ((BT3 >= 901) && (BT3 < 918))
  {
    BT3 = 720;
  }
  else if ((BT3 >= 918) && (BT3 < 935))
  {
    BT3 = 730;
  }
  else if ((BT3 >= 935) && (BT3 < 952))
  {
    BT3 = 740;
  }
  else if ((BT3 >= 952) && (BT3 < 969))
  {
    BT3 = 750;
  }
  else if ((BT3 >= 969) && (BT3 < 986))
  {
    BT3 = 760;
  }
  else if ((BT3 >= 986) && (BT3 < 1003))
  {
    BT3 = 770;
  }
  else if ((BT3 >= 1003) && (BT3 < 1023))
  {
    BT3 = 780;
  }
  ///////////
  if (BT5 < 68)
  {
    BT5 = -1;
  }
  else if ((BT5 >= 68) && (BT5 < 136))
  {
    BT5 = -2;
  }
  else if ((BT5 >= 136) && (BT5 < 204))
  {
    BT5 = -3;
  }
  else if ((BT5 >= 204) && (BT5 < 272))
  {
    BT5 = -4;
  }
  else if ((BT5 >= 272) && (BT5 < 340))
  {
    BT5 = -5;
  }
  else if ((BT5 >= 340) && (BT5 < 408))
  {
    BT5 = -6;
  }
  else if ((BT5 >= 408) && (BT5 < 476))
  {
    BT5 = -7;
  }
  else if ((BT5 >= 476) && (BT5 < 544))
  {
    BT5 = -8;
  }
  else if ((BT5 >= 544) && (BT5 < 612))
  {
    BT5 = -9;
  }
  else if ((BT5 >= 612) && (BT5 < 680))
  {
    BT5 = -10;
  }
  else if ((BT5 >= 680) && (BT5 < 748))
  {
    BT5 = -11;
  }
  else if ((BT5 >= 748) && (BT5 < 816))
  {
    BT5 = -12;
  }
  else if ((BT5 >= 816) && (BT5 < 884))
  {
    BT5 = -13;
  }
  else if ((BT5 >= 884) && (BT5 < 952))
  {
    BT5 = -14;
  }
  else if ((BT5 >= 952) && (BT5 < 1023))
  {
    BT5 = -15;
  }

  //BT1 = map(BT1, 0, 1023, 0, 150);  // hit tho
  BT2 = map(BT2, 0, 1023, 6, 40); // nhip tho
  //BT3 = map(BT3, 0, 1023, 0, 1000); // the tich
  BT4 = map(BT4, 0, 1023, 0, 30); // van  toc
  //BT5 = map(BT5, 0, 1023, 0, 5); // Do Nhay
  //BT5 = BT5 * 5 / 1023; // Do Nhay
  //  float BT = BT1 / 100.0;
  String Dulieu = "a" + bt1 + "b" + String(BT2) + "c" + String(BT3) + "d" + String(BT4) + "e"
                  + String(BT5) + "f" ;
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
  apxuat = pression * 10.1974 ;
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
  GocQuay = map(TheTich, 200, 600, 84, 180); // thể tích từ 0->1000 => Goc
  VanTocTien = (GocQuay / 360.0) * (60.0 * 1000 / ThoiGianhitDC);
  VanTocLui = (GocQuay / 360.0) * (60.0 * 1000 / ThoiGianThoDC);
  t=(ThoiGianTho-((GocQuay/83.0)/60.0));   // time delay Miligiay
  PWMTien = ARRvao[int(VanTocTien)];                    //VanTocTien; ARRvao
  PWMLui =  ARRra[int(VanTocLui)] ;               //ARRra[int(VanTocLui)]  ;//VanTocLui;
  //   BT4 = map(BT4, 0, 1023, 0, 30);
  //  PWMVanToc = 60  ; //VanToc;
  Serial.println((ThoiGianTho-((GocQuay/83.0)/60.0))*1000);
  Serial.println(String(GocQuay) + " " + String(VanTocTien) + " " + String(VanTocLui));
  //   PWMTien=70;
  // PWMLui=50;
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
    DongCo(1, 60);
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
  //String bt1 = Str.substring(Str.indexOf("f") + 1, Str.indexOf("g"));
  if (Mode == 1)
  {
    if (TrangThaiHienThi == "ConFig")
    {
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   SET UP CONTROL " );
      lcd.setCursor(0, 1);
      lcd.print("Nhip Tho : " + String(BT2) + "  N/P");
      lcd.setCursor(0, 2);
      lcd.print("I/E      : " + BT1 );
      lcd.setCursor(0, 3);
      lcd.print("TheTich  : " + String(BT3) + " Cm3" );
    }
    else
    {
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("      CONTROL " );
      lcd.setCursor(0, 1);
      lcd.print("Nhip Tho: " + String(NhipTho) + "  N/P");
      lcd.setCursor(0, 2);
      lcd.print("I/E     : " + BT1  ); //String(HitTho)
      lcd.setCursor(0, 3);
      lcd.print("The Tich: " + String(TheTich) + " Cm3" );
    }
  }
  if (Mode == 2)
  {
    if (TrangThaiHienThi == "ConFig")
    {
      // lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("   SET UP SUPPORT !" );
      lcd.setCursor(0, 1);
      lcd.print(" Ap Xuat : " + String(BT4) + "cmH2O  " );
      lcd.setCursor(0, 2);
      lcd.print(" Do Nhay : " + String(BT5) + "cmH2O  " );
    }
    else
    {
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("     SUPPORT !" );
      lcd.setCursor(0, 1);
      lcd.print(" Ap Xuat : " + String(VanToc) + " cmH2O" );
      lcd.setCursor(0, 2);
//      lcd.print(" Test : " + String(apxuat) + " cmH2O" );
//      lcd.setCursor(0, 3);
      lcd.print(" Do Nhay : " + String(DoNhay) + "cmH2O" );

    }
  }
}
void Timer001s()
{

  
  if (GiaiDoan == 1)
  {
    x++;
    if (x >= (ThoiGianhitDC / 10)) // // ThoiGianhitDC   70
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
  
 
  if (Mode == 2)
  {
    if (CanhBao1 == 1)
    {
      DemCanhBao1++;
    }
    if (DemCanhBao1 > 2000)
    {
      Buzzer(1);
    }
  }
  else
  {
    CanhBao1 = 0;
  }

}
