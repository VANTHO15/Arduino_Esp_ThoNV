
#include <SoftwareSerial.h>
const byte RX = 2;
const byte TX = 3;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

#include "DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT11
const byte  Switch1 = 4;
const byte  Switch2 = 5;
const byte  Switch3 = 6;
const byte  Switch4 = 7;

const byte  TB1 = 8;
const byte  TB2 = 9;
const byte  TB3 = 10;
const byte  TB4 = 11;

int trangthairelay1 = 0;
int trangthairelay2 = 0;
int trangthairelay3 = 0;
int trangthairelay4 = 0;

long nhietdo = 0;
long doam = 0;
int bien1 = 0;
int bien2 = 0;

String A = "A";
String B = "B";
String C = "C";
String D = "D";
String E = "E";
String F = "F";
String G = "G";
String ChuoiSendESP = "";
long last = 0;
int nhietdocaidat = 30;
int doamcaidat = 50;

String slaver = "J1K";
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  //dht.begin();
  pinMode(Switch1 , INPUT_PULLUP);
  pinMode(Switch2 , INPUT_PULLUP);
  pinMode(Switch3 , INPUT_PULLUP);
  pinMode(Switch4 , INPUT_PULLUP);

  pinMode(TB1 , OUTPUT);
  pinMode(TB2 , OUTPUT);
  pinMode(TB3, OUTPUT);
  pinMode(TB4 , OUTPUT);

  digitalWrite(TB1, HIGH);
  digitalWrite(TB2, HIGH);
  digitalWrite(TB3, HIGH);
  digitalWrite(TB4, HIGH);
  Serial.println("Start");
  last = millis();

}

void loop()
{
  
  RemoteFR();
  Sosanh();
  Read_UART();
  if (millis() - last >= 1000)
  {
    chuongtrinhcambien();
    Serial.print("Nhiệt độ:");
    Serial.println(nhietdo);
    Serial.print("Độ ẩm:");
    Serial.println(doam);
    Serial.print("trangthairelay1:");
    Serial.println(trangthairelay1);
    Serial.print("trangthairelay2:");
    Serial.println(trangthairelay2);
    Serial.print("trangthairelay3:");
    Serial.println(trangthairelay3);
    Serial.print("trangthairelay4:");
    Serial.println(trangthairelay4);
    

    last = millis();
  }
}
void Sosanh()
{
  if (nhietdo >= nhietdocaidat)
  {
    // làm việc gì đó
  }
  else
  {

  }
  if (doam >= doamcaidat)
  {
    // làm việc gì đó
  }
  else
  {

  }
}
void Read_UART()
{
  while (mySerial.available())
  {
    char inChar = (char)mySerial.read();

    inputString += inChar;

    if (inChar == '\n')
    {
      stringComplete = true;
    }
    if (stringComplete)
    {
      Serial.print("Data nhận được là:");
      Serial.println(inputString);
      
    
      //=====================================
      if (inputString.indexOf("A0B") >= 0)
      {
        Serial.println("OFF thiết bị 1");
        digitalWrite(TB1, HIGH);
        trangthairelay1 = 0;
      }
      else if (inputString.indexOf("A1B") >= 0)
      {
        Serial.println("ON thiết bị 1");
        digitalWrite(TB1, LOW);
        trangthairelay1 = 1;
      }

      if (inputString.indexOf("C0D") >= 0)
      {
        Serial.println("OFF thiết bị 2");
        digitalWrite(TB2, HIGH);
        trangthairelay2 = 0;
      }
      else if (inputString.indexOf("C1D") >= 0)
      {
        Serial.println("ON thiết bị 2");
        digitalWrite(TB2, LOW);
        trangthairelay2 = 1;
      }
      int TimE , TimF , TimG, TimH = -1;  // E...F
      TimE = inputString.indexOf("E");
      TimF = inputString.indexOf("F");
      TimG = inputString.indexOf("G");
      TimH = inputString.indexOf("H");
      // Bước 2
      // if có chức xác thực có tồn tại dữ liệu để làm việc
      if (TimE >= 0 && TimF >= 0 )
      {
        String dulieu1 = "";
        //Tách dữ liệu
        dulieu1 = inputString.substring(TimE + 1, TimF);
        Serial.print("Dữ liệu 1:");
        Serial.println(dulieu1);
        //
        bien1 = dulieu1.toInt(); // 1234 String => toInt() 1234 string => int 1234
        Serial.print("bien1:");
        Serial.println(bien1);

      }
      if (TimG >= 0 && TimH >= 0 )
      {
        String dulieu2 = "";
        //Tách dữ liệu
        dulieu2 = inputString.substring(TimG + 1, TimH);
        Serial.print("Dữ liệu 2:");
        Serial.println(dulieu2);
        //
        bien2 = dulieu2.toInt();
        Serial.print("bien2:");
        Serial.println(bien2);
      }
      if (inputString.indexOf("JK") >= 0)
      {
        // lênh esp yêu gửi dữ liệu về
        sendata();
      }
      //=====================================

      inputString = "";
      stringComplete = false;
    }

  }
}
void RemoteFR()
{
  if (digitalRead(Switch1) ==  1)
  {
    delay(200);
    while (1)
    {
      Read_UART();
      if (digitalRead(Switch1) ==  0)
      {
        if (trangthairelay1 == 0)
        {
          Serial.println(">> ON TB 1");
          digitalWrite(TB1, LOW);
          trangthairelay1 = 1;
        }
        else if (trangthairelay1 == 1)
        {
          Serial.println(">> OFF TB 1");
          digitalWrite(TB1, HIGH);
          trangthairelay1 = 0;
        }
        break;
      }
    }
  }


  if (digitalRead(Switch2) ==  1)
  {
    delay(200);
    while (1)
    {
      Read_UART();
      if (digitalRead(Switch2) ==  0)
      {
        if (trangthairelay2 == 0)
        {
          Serial.println(">> ON TB 2");
          digitalWrite(TB2, LOW);
          trangthairelay2 = 1;
        }
        else if (trangthairelay2 == 1)
        {
          Serial.println(">> OFF TB 2");
          digitalWrite(TB2, HIGH);
          trangthairelay2 = 0;
        }
        break;
      }
    }
  }


  if (digitalRead(Switch3) ==  1)
  {
    delay(200);
    while (1)
    {
      Read_UART();
      if (digitalRead(Switch3) ==  0)
      {
        if (trangthairelay3 == 0)
        {
          Serial.println(">> ON TB 3");
          digitalWrite(TB1, LOW);
          trangthairelay3 = 1;
        }
        else if (trangthairelay3 == 1)
        {
          Serial.println(">> OFF TB 3");
          digitalWrite(TB3, HIGH);
          trangthairelay3 = 0;
        }
        break;
      }
    }
  }


  if (digitalRead(Switch4) ==  1)
  {
    delay(200);
    while (1)
    {
      Read_UART();
      if (digitalRead(Switch4) ==  0)
      {
        if (trangthairelay4 == 0)
        {
          Serial.println(">> ON TB 4");
          digitalWrite(TB1, LOW);
          trangthairelay4 = 1;
        }
        else if (trangthairelay4 == 1)
        {
          Serial.println(">> OFF TB 4");
          digitalWrite(TB4, HIGH);
          trangthairelay4 = 0;
        }
        break;
      }
    }
  }
}

void chuongtrinhcambien()
{
  doam++;
  nhietdo++;
}

void sendata()
{
  // khung truyền dữ liệu truyền về đảm bảo cái vấn đề không bị lỗi dữ liệu và xác định được dữ liệu
  //A[nhietdo]B[doam]C[anhsang]D[trangthaithietbi1]E[trangthaithietbi2]F
  chuongtrinhcambien();
  ChuoiSendESP = "";
  ChuoiSendESP = A + nhietdo + B + doam + C + trangthairelay1 + D + trangthairelay2 + E;
  mySerial.println(ChuoiSendESP); // gửi dữ liệu qua esp  //A0B0C0D1E0F\n
  mySerial.flush();
  Serial.print("ChuoiSendESP:");
  Serial.println(ChuoiSendESP);

}
