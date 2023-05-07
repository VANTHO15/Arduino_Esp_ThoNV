
//chân ST_CP của 74HC595
int latchPin = 8;
//chân SH_CP của 74HC595
int clockPin = 12;
//Chân DS của 74HC595
int dataPin = 11;

//Trạng thái của LED, hay chính là byte mà ta sẽ gửi qua shiftOut
byte ledStatus;
void setup() {
  //Bạn BUỘC PHẢI pinMode các chân này là OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() { 
  /*
    Trong tin học, ngoài các phép +, -, *, / hay % mà bạn đã biết trên hệ cơ số 10.
    Thì còn có nhiều phép tính khác nữa. Và một trong số đó là Bit Math (toán bit) trên hệ cơ số 2.
    Để hiểu những gì tôi viết tiếp theo sau, bạn cần có kiến thức về Bit Math.
    Để tìm hiểu về Bit Math, bạn vào mục Tài liệu tham khảo ở bảng chọn nằm phía trên cùng trang web và chạy xuống khi bạn kéo chuột trên trang Arduino.VN
    
  */
  //Sáng tuần tự
  ledStatus = 0;//mặc định là không có đèn nào sáng hết (0 = 0b00000000)
  for (int i = 0; i < 8; i++) {
    ledStatus = (ledStatus << 1) | 1;//Đẩy toàn bộ các bit qua trái 1 bit và cộng bit có giá trị là 1 ở bit 0  
    
    /**
      Bắt buộc phải có để shiftOut
    **/
    
    digitalWrite(latchPin, LOW); //các đèn LED sẽ không sáng khi bạn digital LOW
 
    //ShiftOut ra IC
    shiftOut(dataPin, clockPin, MSBFIRST, ledStatus);  

    digitalWrite(latchPin, HIGH);//các đèn LED sẽ sáng với trạng thái vừa được cập nhập
   
    /**
      Kết thúc bắt buộc phải có
    **/
    
    delay(500); // Dừng chương trình khoảng 500 mili giây để thấy các hiệu ứng của đèn LED
  }
  
  //Tắt tuần tự
  for (int i = 0;i<8;i++) {
    ledStatus <<= 1; //Đẩy tất cả các bit qua bên trái 1 bit
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, ledStatus);  
    digitalWrite(latchPin, HIGH);
    delay(500);
  }
}
