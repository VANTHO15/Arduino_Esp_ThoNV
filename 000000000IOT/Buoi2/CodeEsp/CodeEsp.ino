#include <SoftwareSerial.h> //2.5.0
const byte RX = D6;
const byte TX = D5;
SoftwareSerial mySerial = SoftwareSerial(RX, TX);
String inputString = "";
bool stringComplete = false;

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
String G = "G";
String H = "H";
long last = 0;
int trangthairelay1 = 0;
int trangthairelay2 = 0;
void setup()
{
  Serial.begin(9600);
  while (!Serial);
  mySerial.begin(9600);
  while (!mySerial);
  Serial.println("Start");

  last = millis();
}

void loop()
{
  Read_Uart();
  if (millis() - last >= 2000)
  {
    YeuCau();
    last = millis(); // bien1 = 123 , bien2 = 0 ;
  }

}


void YeuCau()
{
  String Lenh = "";
  Lenh = G + H;
  mySerial.println(Lenh); // gửi đi
  mySerial.flush();// đợi truyền hết chuỗi gửi đi
  Serial.print(">>Đã gửi lệnh:");
  Serial.println(Lenh);
}



void Read_Uart()
{
  while (mySerial.available())// A279B290C315D0E\n
  {
    char inChar = (char)mySerial.read();
    inputString += inChar;
    if (inChar == '\n')
    {
      stringComplete = true;
    }
    if (stringComplete)
    {
      Serial.print("Data nhận Uno = ");
      Serial.println(inputString);

      //=====================================
      /*
         Bước 1: tìm kí tự A B C D Etrong chuỗi gửi xuống
         Bước 2: Tách dữ liệu
         Bước 3: gắn cho 1 biến => json( server)
      */
      int TimA, TimB, TimC , TimD, TimE  = -1;
      TimA = inputString.indexOf("A");
      TimB = inputString.indexOf("B");
      TimC = inputString.indexOf("C");
      TimD = inputString.indexOf("D");
      TimE = inputString.indexOf("E");

      if (TimA >= 0 && TimB >= 0 && TimE >= 0)
      {
        String datanhietdo, datadoam, relay1 , relay2 = "";
        datanhietdo  = inputString.substring( TimA + 1 , TimB);
        datadoam  = inputString.substring( TimB + 1 , TimC);
        relay1   = inputString.substring( TimC + 1 , TimD);
        relay2  = inputString.substring( TimD + 1 , TimE);

        nhietdo = datanhietdo.toInt();
        doam = datadoam.toInt();
        trangthairelay1 = relay1.toInt();
        trangthairelay2 =  relay2.toInt();

        Serial.print("nhietdo:");
        Serial.println(nhietdo);
        Serial.print("doam :");
        Serial.println(doam );
        Serial.print("trangthairelay1:");
        Serial.println(trangthairelay1);
        Serial.print("trangthairelay2:");
        Serial.println(trangthairelay2);

        //{"nhietdo":"111", "doam":"222" , "anhsang":"333" , "bien":"4444"}

        //{\"nhietdo\":\"111\", \"doam\":\"222\" , \"anhsang\":\"333\" , \"bien\":\"4444\"}

        String json = "";
        json = "{\"nhietdo\":\"" + String(nhietdo) + "\", \"doam\":\"" + String(doam) + "\" ,\"trangthairelay1\":\"" + String(trangthairelay1) + "\" ,\"trangthairelay2\":\"" + String(trangthairelay2) + "\"}";
        Serial.print("json:");
        Serial.println(json);
      }

      //=====================================
      inputString = "";
      stringComplete = false;
    }
  }
}
