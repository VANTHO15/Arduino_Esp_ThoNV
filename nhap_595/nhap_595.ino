int a[10] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};
#include <Wire.h>
#include   <EEPROM.h>
#define DS1307 0x68
int  hienthi(int n)
{
  int x = a[n];
  for (int i = 4; i <= 11; i++)
  {
    digitalWrite(i, x & 0x01);
    x = x >> 1;
  }
}
int mode = 1, t_hen_gio = 6, t_hen_phut = 0;
int nhiet_do = 0;
int  S10_nhiet_do = 0; // 10s lấy nhiệt đọ 1 lần
int second, minute, hour, day, wday, month, year;
int  sang(int a, int b)
{
  hienthi(a / 10);
  digitalWrite(A0, 0);
  digitalWrite(A1, 1);
  digitalWrite(A2, 1);
  digitalWrite(A3, 1);
  delay(5);
  digitalWrite(A0, 1);
  hienthi(a % 10);
  digitalWrite(A1, 0);
  digitalWrite(A2, 1);
  digitalWrite(A3, 1);
  delay(5);
  digitalWrite(A1, 1);
  hienthi(b / 10);
  digitalWrite(A2, 0);
  digitalWrite(A0, 1);
  digitalWrite(A1, 1);
  digitalWrite(A3, 1);
  delay(5);
  digitalWrite(A2, 1);
  hienthi(b % 10);
  digitalWrite(A3, 0);
  digitalWrite(A0, 1);
  digitalWrite(A1, 1);
  delay(5);
  digitalWrite(A3, 1);
}
//chân ST_CP của 74HC595
int latchPin = 0;
//chân SH_CP của 74HC595
int clockPin = 12;
//Chân DS của 74HC595
int dataPin = 1;
//Trạng thái của LED, hay chính là byte mà ta sẽ gửi qua shiftOut
const int HC595_COUNT = 2;
byte ledStatus[HC595_COUNT] = {0};
void setup() {
  Wire.begin();
  setTime(10, 20, 00, 1, 9, 1, 19); // 12:30:45 CN
  //Bạn BUỘC PHẢI pinMode các chân này là OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
//  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); // nut bam mode
  pinMode(13, OUTPUT);       // buzzo
  digitalWrite(13, 0);
  pinMode(3, INPUT_PULLUP); // tăng 10p nếu bấm 1 lần
  attachInterrupt(digitalPinToInterrupt(2), tho_hen_gio, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), tho_tang_phut, FALLING);
  for (int i = 4; i <= 11; i++)
  { pinMode(i, OUTPUT);
    digitalWrite(i, 0);
  }
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A0, 1);
  digitalWrite(A1, 1);
  digitalWrite(A2, 1);
  digitalWrite(A3, 1);
  Serial.begin(9600);
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;
  TCCR1B |= 1 << CS12;
  TCNT1 = 3036;
  TIMSK1 = (1 << TOIE1);
  sei();
}
void fillValueToArray(byte value)
{
  for (int i = 0; i < HC595_COUNT; i += 1)
    ledStatus[i] = value;
}

void shiftOutHC595(int dataPin, int clockPin, byte ledStatus[])
{
  digitalWrite(latchPin, LOW);
  for (int i = 0; i < HC595_COUNT; i++) {
    shiftOut(dataPin, clockPin, MSBFIRST, ledStatus[i]);
  }
  digitalWrite(latchPin, HIGH);
}

//sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);

void  sang_tho(int mode, int hour, int minute, int hen_gio, int hen_phut, float nhiet_do)
{
  if (mode == 1) sang(hour, minute);
  if (mode == 3) sang(hen_gio, hen_phut);
  if (mode == 2) sang(nhiet_do, 0);
}
int  hen_gio = 6;    //EEPROM.read(0);
int  hen_phut = 30;   //EEPROM.read(1);
void loop()
{
 
  sang_tho(mode, hour, minute, hen_gio, hen_phut, nhiet_do);
  readDS1307();
  digitalClockDisplay();
  sang_tho(mode, hour, minute, hen_gio, hen_phut, nhiet_do);
//  vì ledStatus là một mảng vì vậy để mặc định tất cả đèn tắt thì chúng ta phải for đến từng giá trị của mảng rồi đặt giá trị là 0.
    fillValueToArray(0);
    //Bật tuần tự
    for (int i = 0; i < HC595_COUNT; i++) {
      for (byte j = 0; j < 8; j++) {
        ledStatus[i] = (ledStatus[i] << 1) | 1;
        shiftOutHC595(dataPin, clockPin, ledStatus);
        delay(1000);
        sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
      }
    }
    //Tắt tuần tự
    for (int i = 0; i < HC595_COUNT; i++)
    {
      for (byte j = 0; j < 8; j++)
      {
        ledStatus[i] = (ledStatus[i] << 1);
        shiftOutHC595(dataPin, clockPin, ledStatus);
        delay(100);
        sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
      }
    }
    //Nhấp nháy nhanh
    for (byte k = 0; k < 50; k++)
    {
      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
      fillValueToArray(0b10101010);
      shiftOutHC595(dataPin, clockPin, ledStatus);
      delay(50);
      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
      fillValueToArray(0b01010101);
      shiftOutHC595(dataPin, clockPin, ledStatus);
      delay(50);
      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
    }
    //sáng 1 đèn rồi cách 1 đèn ko sáng rồi lại sáng những đèn chưa bật
    for (int k = 1; k <= 3; k++)
    {
      fillValueToArray(0);
      for (int i = 0; i < HC595_COUNT; i++)
      {
        sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
        for (byte j = 0; j < 8; j += 2)
        {
          ledStatus[i] |= 1 << j;
          shiftOutHC595(dataPin, clockPin, ledStatus);
          delay(100);
          sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
        }
      }
      for (int i = 0; i < HC595_COUNT; i++)
      {
        sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
        for (byte j = 1; j < 8; j += 2)
        {
          ledStatus[i] |= 1 << j;
          shiftOutHC595(dataPin, clockPin, ledStatus);
          delay(100);
          sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
        }
      }
    }
  
    //Tắt dần theo thứ tự trên
    for (int i = HC595_COUNT - 1; i >= 0; i--)
    {
      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
      for (int j = 7; j >= 0; j -= 2)
      {
        ledStatus[i] &= ~(1 << j);
        shiftOutHC595(dataPin, clockPin, ledStatus);
        delay(200);
        sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
      }
    }
    for (int i = HC595_COUNT - 1; i >= 0; i--)
    {
      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
      for (int j = 6; j >= 0; j -= 2)
      {
        sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
        ledStatus[i] &= ~(1 << j);
        shiftOutHC595(dataPin, clockPin, ledStatus);
        delay(200);
      }
    }
  
    /// Hãy khám phá thế giới lập trình này nhé :)
    fillValueToArray(0);
    //Bật tuần tự
    for (int i = 0; i < HC595_COUNT; i++)
    {
      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
      for (byte j = 0; j < 8; j++)
      {
        ledStatus[i] = (ledStatus[i] << 1) | 1;
        shiftOutHC595(dataPin, clockPin, ledStatus);
        delay(50); // Dừng chương trình khoảng 500 mili giây để thấy các hiệu ứng của đèn LED
        sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
      }
    }
  
    //    Tắt tuần tự
    for (int i = 0; i < HC595_COUNT; i++) {
      for (byte j = 0; j < 8; j++) {
        sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
        ledStatus[i] = (ledStatus[i] << 1);
        shiftOutHC595(dataPin, clockPin, ledStatus);
        delay(50); // Dừng chương trình khoảng 500 mili giây để thấy các hiệu ứng của đèn LED
      }
    }
    //////
//    for (byte k = 0; k < 10; k++)
//    {
//      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
//      fillValueToArray(0);
//      fillValueToArray(0b00000001);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      delay(200);
//      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
//      fillValueToArray(0b00000001);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      sang(04, 45);
//      delay(200);
//      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
//      fillValueToArray(0b00000011);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      delay(200);
//      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
//      fillValueToArray(0b00000011);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      delay(200);
//      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
//      fillValueToArray(0b00000111);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      sang(04, 45);
//      delay(200);
//      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
//      fillValueToArray(0b00000111);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
//      delay(200);
//      fillValueToArray(0b00001111);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      delay(200);
//      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
//      fillValueToArray(0b00001111);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
//      delay(200);
//      fillValueToArray(0b00011111);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      delay(200);
//      fillValueToArray(0b00011111);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      delay(200);
//      fillValueToArray(0b00111111);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
//      delay(200);
//      fillValueToArray(0b00111111);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      delay(200);
//      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
//      fillValueToArray(0b01111111);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      delay(200);
//      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
//      fillValueToArray(0b01111111);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      delay(200);
//      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
//      fillValueToArray(0b11111111);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      delay(200);
//      sang_tho(mode,hour,minute,hen_gio,hen_phut,nhiet_do);
//      fillValueToArray(0b11111111);
//      shiftOutHC595(dataPin, clockPin, ledStatus);
//      delay(200);
//    }
}
// time 1 giây.,.,.,..,.,.,.,.,.,.,.,,.,
ISR  (TIMER1_OVF_vect)
{
  TCNT1 = 3036;
  digitalWrite(4, !digitalRead(4)); // nháy 1 giây
  S10_nhiet_do++;
  if (S10_nhiet_do == 10)
  {
    float n = analogRead(A6);
    float nhiet = (n * 500 / 1023);
    nhiet_do = int(nhiet);
    S10_nhiet_do = 0;
  }
}
void  tho_hen_gio()
{
  delayMicroseconds(200);
  while (digitalRead(2) == 0) ;
  delayMicroseconds(200);
  mode++;
  if (mode == 4) mode = 1;
}
//         còi.........................
void  buzzo()
{
  digitalWrite(1, 1);
  delay(50);
  digitalWrite(1, 0);
  delay(50);
  digitalWrite(1, 1);
  delay(50);
  digitalWrite(1, 0);
  delay(50);
  digitalWrite(1, 1);
  delay(50);
}
void  tho_tang_phut()
{
  delayMicroseconds(200);
  while (digitalRead(3) == 0) ;
  delayMicroseconds(200);
  if (mode == 3)
  {
    hen_phut += 10;
    if (hen_phut == 60)
    {
      hen_phut = 0;
      hen_gio++;
      if (hen_gio == 24)  hen_gio = 0;
    }
  }
}
void readDS1307()
{
  Wire.beginTransmission(DS1307);
  Wire.write((byte)0x00);
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);
  second = bcd2dec(Wire.read() & 0x7f);
  minute = bcd2dec(Wire.read() );
  hour   = bcd2dec(Wire.read() & 0x3f); // chế độ 24h.
  wday   = bcd2dec(Wire.read() );
  day    = bcd2dec(Wire.read() );
  month  = bcd2dec(Wire.read() );
  year   = bcd2dec(Wire.read() );
  year += 2000;
}
int bcd2dec(byte num)
{
  return ((num / 16 * 10) + (num % 16));
}
int dec2bcd(byte num)
{
  return ((num / 10 * 16) + (num % 10));
}
void digitalClockDisplay() {
  Serial.print(hour);
  printDigits(minute);
  printDigits(second);
  Serial.print(" ");
  Serial.print(day);
  Serial.print(" ");
  Serial.print(month);
  Serial.print(" ");
  Serial.print(year);
  Serial.println();
}

void printDigits(int digits) {
  // các thành phần thời gian được ngăn chách bằng dấu :
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
void setTime(byte hr, byte min, byte sec, byte wd, byte d, byte mth, byte yr)
{
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0x00)); // đặt lại pointer
  Wire.write(dec2bcd(sec));
  Wire.write(dec2bcd(min));
  Wire.write(dec2bcd(hr));
  Wire.write(dec2bcd(wd)); // day of week: Sunday = 1, Saturday = 7
  Wire.write(dec2bcd(d));
  Wire.write(dec2bcd(mth));
  Wire.write(dec2bcd(yr));
  Wire.endTransmission();
}
