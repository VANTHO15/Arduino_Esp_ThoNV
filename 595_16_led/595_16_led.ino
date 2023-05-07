//chân ST_CP của 74HC595
int latchPin = 10;  //10
//chân SH_CP của 74HC595
int clockPin = 12;  //12
//Chân DS của 74HC595
int dataPin = 11;    //11
//Trạng thái của LED, hay chính là byte mà ta sẽ gửi qua shiftOut
const int HC595_COUNT = 2;//Nếu bạn dùng nhiều hơn thì thay bằng một số lớn hơn 2.
byte ledStatus[HC595_COUNT] = {0};
void setup() {
  //Bạn BUỘC PHẢI pinMode các chân này là OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT) ;
  pinMode(dataPin, OUTPUT);
  
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
void loop() {

  //vì ledStatus là một mảng vì vậy để mặc định tất cả đèn tắt thì chúng ta phải for đến từng giá trị của mảng rồi đặt giá trị là 0.
  fillValueToArray(0);
  //Bật tuần tự
  for (int i = 0; i < HC595_COUNT; i++) {
    for (byte j = 0; j < 8; j++) {
      ledStatus[i] = (ledStatus[i] << 1) | 1;
      shiftOutHC595(dataPin, clockPin, ledStatus);
      delay(1000);
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
    }
  }
  //Nhấp nháy nhanh
  for (byte k = 0; k < 50; k++)
  {
    fillValueToArray(0b10101010);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(50);
    fillValueToArray(0b01010101);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(50);
  }
  //sáng 1 đèn rồi cách 1 đèn ko sáng rồi lại sáng những đèn chưa bật
  for (int k = 1; k <= 3; k++)
  {
    fillValueToArray(0);
    for (int i = 0; i < HC595_COUNT; i++)
    {
      for (byte j = 0; j < 8; j += 2)
      {
        ledStatus[i] |= 1 << j;
        shiftOutHC595(dataPin, clockPin, ledStatus);
        delay(100);
      }
    }
    for (int i = 0; i < HC595_COUNT; i++)
    {
      for (byte j = 1; j < 8; j += 2)
      {
        ledStatus[i] |= 1 << j;
        shiftOutHC595(dataPin, clockPin, ledStatus);
        delay(100);
      }
    }
  }

  //Tắt dần theo thứ tự trên
  for (int i = HC595_COUNT - 1; i >= 0; i--)
  {
    for (int j = 7; j >= 0; j -= 2)
    {
      ledStatus[i] &= ~(1 << j);
      shiftOutHC595(dataPin, clockPin, ledStatus);
      delay(200);
    }
  }
  for (int i = HC595_COUNT - 1; i >= 0; i--)
  {
    for (int j = 6; j >= 0; j -= 2)
    {
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
    for (byte j = 0; j < 8; j++)
    {
      ledStatus[i] = (ledStatus[i] << 1) | 1;
      shiftOutHC595(dataPin, clockPin, ledStatus);
      delay(50); // Dừng chương trình khoảng 500 mili giây để thấy các hiệu ứng của đèn LED
    }
  }

  //    Tắt tuần tự
  for (int i = 0; i < HC595_COUNT; i++) {
    for (byte j = 0; j < 8; j++) {
      ledStatus[i] = (ledStatus[i] << 1);
      shiftOutHC595(dataPin, clockPin, ledStatus);
      delay(50); // Dừng chương trình khoảng 500 mili giây để thấy các hiệu ứng của đèn LED
    }
  }
  //////
  for (byte k = 0; k < 10; k++)
  {
    fillValueToArray(0);
    fillValueToArray(0b00000001);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b00000001);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b00000011);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b00000011);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b00000111);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b00000111);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b00001111);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b00001111);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b00011111);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b00011111);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b00111111);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b00111111);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b01111111);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b01111111);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b11111111);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
    fillValueToArray(0b11111111);
    shiftOutHC595(dataPin, clockPin, ledStatus);
    delay(200);
  }
}
