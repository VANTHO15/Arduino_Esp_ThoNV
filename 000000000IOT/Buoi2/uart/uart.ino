#include <SoftwareSerial.h> //2.5.0
const byte RX = 2;
const byte TX = 3;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);
String inputString = "";
bool stringComplete = false;

#define TB1 4
#define TB2 5
#define nutnhan1 6
#define nutnhan2 7

int trangthairelay1 = 0;
int trangthairelay2 = 0;

long bien = 0;
String SendESP = "";
int nhietdo = 0;
int doam = 0;
int anhsang = 0;
String A = "A";
String B = "B";
String C = "C";
String D = "D";
String E = "E";
long last = 0;

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  mySerial.begin(9600);
  while (!mySerial);
  // khai báo output
  pinMode(TB1, OUTPUT);
  pinMode(TB2, OUTPUT);

  pinMode(nutnhan1, INPUT_PULLUP);
  pinMode(nutnhan2, INPUT_PULLUP);

  digitalWrite(TB1, HIGH);
  digitalWrite(TB2, HIGH);
  Serial.println("Start");
  Serial.print("bien:");
  Serial.println(bien);
  last = millis();
}

void loop()
{
  read_uart();
  button();
  /*
    if (millis() - last >= 2000)
    {
     send_dulieu();
     last = millis(); // bien1 = 123 , bien2 = 0 ;
    }
  */

}
void button()
{
  if (digitalRead(nutnhan1) == LOW)
  {
    delay(200);
    if (digitalRead(nutnhan1) == HIGH)
    {
      Serial.println("điều khiển thiết bị 1");
      if (trangthairelay1 == 0)
      {
        Serial.println("ON thiet bi 1");
        digitalWrite(TB1, LOW);
        trangthairelay1 = 1;
      }
      else if (trangthairelay1 == 1)
      {
        Serial.println("OFF thiet bi 1");
        digitalWrite(TB1, HIGH);
        trangthairelay1 = 0;
      }
    }
  }

  if (digitalRead(nutnhan2) == LOW)
  {
    delay(200);
    if (digitalRead(nutnhan2) == HIGH)
    {
      Serial.println("điều khiển thiết bị 2");
      if (trangthairelay2 == 0)
      {
        Serial.println("ON thiet bi 1");
        digitalWrite(TB2, LOW);
        trangthairelay2 = 1;
      }
      else if (trangthairelay2 == 1)
      {
        Serial.println("OFF thiet bi 2");
        digitalWrite(TB2, HIGH);
        trangthairelay2 = 0;
      }
    }
  }
}

void send_dulieu()
{
  //3 lệnh
  // Dữ liệu gửi đi là gì ( String)
  // Gửi đi
  // ĐỢi gửi hết rồi làm viêc
  // Gửi nhiet do , độ ẩm , ánh sáng
  SendESP = "";
  nhietdo = analogRead(A0);
  doam = analogRead(A1);
  anhsang = analogRead(A2);
  // khởi tạo cấu trúc chung để truyền dữ liệu => phân biệt dữ liệu , tránh trường hợp hiểu nhầm , lỗi
  // A[nhiệt độ]B[độ ẩm]C[ánh sáng]D
  SendESP = A + nhietdo + B + doam + C + trangthairelay1 + D + trangthairelay2 + E; //A123B456C122D
  mySerial.println(SendESP); // gửi đi
  mySerial.flush();// đợi truyền hết chuỗi gửi đi
  Serial.print("SendESP: ");
  Serial.println(SendESP); // A123B456C122D\n
}
void read_uart()
{
  while (mySerial.available())
  {
    char inChar = (char)mySerial.read();// 123456\n
    inputString += inChar;
    if (inChar == '\n')
    {
      stringComplete = true;
    }
    if (stringComplete)
    {
      Serial.println(inputString);
      //=====================================
      // khung dữ liệu điều khiển thiết bị 1 => A[0 1]B
      /*
         Bước 1: tìm kí tự A B trong chuỗi gửi xuống
         Bước 2: Tách dữ liệu
         Bước 3: so sánh điều khiển
      */
      int TimA, TimB = -1;
      TimA = inputString.indexOf("A");
      TimB = inputString.indexOf("B");
      if (TimA >= 0 && TimB >= 0)
      {
        String thietbi1 = "";
        thietbi1 = inputString.substring(TimA + 1 , TimB);
        Serial.print("thietbi1: ");
        Serial.println(thietbi1);
        if (thietbi1.toInt() == 0)
        {
          Serial.println("OFF 1 thiết bị 1");
          digitalWrite(TB1, HIGH);
          trangthairelay1 = 0;
        }
        else if (thietbi1.toInt() == 1)
        {
          Serial.println("ON 1 thiết bị 1");
          digitalWrite(TB1, LOW);
          trangthairelay1 = 1;
        }
      }
      // khung dữ liệu điều khiển thiết bị 1 => C[]D
      int TimC, TimD = -1;
      TimC = inputString.indexOf("C");
      TimD = inputString.indexOf("D");
      if (TimC >= 0 && TimD >= 0)
      {
        String thietbi2 = "";
        thietbi2 = inputString.substring(TimC + 1 , TimD);
        Serial.print("thietbi2: ");
        Serial.println(thietbi2);
        if (thietbi2.toInt() == 0)
        {
          Serial.println("OFF 2 thiết bị 1");
          digitalWrite(TB2, HIGH);
          trangthairelay2 = 0;
        }
        else if (thietbi2.toInt() == 1)
        {
          Serial.println("ON 2 thiết bị 1");
          digitalWrite(TB2, LOW);
          trangthairelay2 = 0;
        }
      }
      //thay đổi dữ liệu của biến gì đó => E[]F
      int TimE, TimF = -1;
      TimE = inputString.indexOf("E");
      TimF = inputString.indexOf("F");
      if (TimE >= 0 && TimF >= 0)
      {
        String dulieu = "";
        dulieu = inputString.substring(TimE + 1 , TimF);
        Serial.print("dulieu: ");
        Serial.println(dulieu);
        bien = dulieu.toInt();
        Serial.print("bien:");
        Serial.println(bien);
      }

      int TimG, TimH = -1;
      TimG = inputString.indexOf("G");
      TimH = inputString.indexOf("H");
      if (TimG >= 0 && TimH >= 0)
      {
        send_dulieu();
      }
      inputString = "";
      stringComplete = false;
    }
  }
}
