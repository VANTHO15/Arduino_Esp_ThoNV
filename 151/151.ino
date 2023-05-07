#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <string.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(13, 15); // RX, TX
#define FIREBASE_HOST "doan-80859.firebaseio.com"
#define FIREBASE_AUTH "u9WFLZXmT2n2Brx4IUyPvzw2RYgpIvkqKo1eAqMP"
#define WIFI_SSID "dell cho pass"
#define WIFI_PASSWORD "bluewind97"
#define hongngoai D1



void setup() {
 pinMode(hongngoai,INPUT);
 // pinMode(D1,INPUT_PULLUP);
  Serial.begin(9600);
  mySerial.begin(9600);
  while(!Serial)
  {
    //Wait for serial port to connect
  }
  delay(2000);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  mySerial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    mySerial.print(".");
    delay(500);
  }
  mySerial.println();
  mySerial.print("connected: ") ;
  mySerial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 // Firebase.stream("/ESP32");
  Firebase.stream("Token");

  
}
void loop()
 { 
   Canhbao() ;
   Cohang() ;
   GetPass() ;
   } 

///Source code 
//////////////////////////////////////////////////
void Canhbao() {
  if (Serial.available() > 0) 
  {
    while (Serial.available() > 0)
    {
      char ch = Serial.read(); 
      if(ch == 'W' )
      {
        Firebase.setFloat("CanhBao",1);
        delay(10);
        Firebase.setFloat("CanhBao",0);
      } 
     } 
  }
}
void Cohang() {
    int b = digitalRead(hongngoai);
      if (b == 1 )
     {
      Firebase.setFloat("TuCoHang",0);
     }
    else if (b == 0 )
     {
      Firebase.setFloat("TuCoHang",1) ; 
     }
    else if (Firebase.failed())
    {
       mySerial.print("setting / number failed : ") ; 
       mySerial.println(Firebase.error() ) ;
       return ;
     } 
     
}
void GetPass() {
    if (Firebase.available()) 
    { 
       FirebaseObject event = Firebase.readEvent();
       String eventType = event.getString("type");
       //Serial.print("event: ");
        //Serial.println(eventType);
       if (eventType == "put")
       {
          String path = event.getString("value");
          String data = event.getString("data");
          // Serial.println(data);
     
          data.toCharArray(Token,6);
         //Serial.write(Token);
          for(int i = 0; i<5;i++) 
          {
            Serial.write(Token[i]);
          }
          mySerial.println();
       }
      
    } 
    
    if (Firebase.failed()) 
    {
      mySerial.println("streaming error");
      mySerial.println(Firebase.error());
    }
}
   
  //Source
  ///////////////////////////////
  /*
  void loop() 
  { 
   int Stt = Firebase.getInt("Status");
    Serial.println(Stt);
    if (Stt == 1 ) 
    {
    digitalWrite(ledPin,HIGH);
    }
    else 
    {
     digitalWrite(ledPin,LOW) ; 
    }
   // Firebase.setFloat("Status",1);
  } */
  ///////////////////////////////
  /* if (Serial.available() > 0) {
    while (Serial.available() > 0) {
      char ch = Serial.read(); 
      if(ch == 'W' ) {
        Firebase.setFloat("CanhBao",1);
        delay(10);
        Firebase.setFloat("CanhBao",0);
       } } }*/
   /////////////////////////////
        /* int b = digitalRead(hongngoai);
      if (b == 1 )
     {
      Firebase.setFloat("TuCoHang",0);
     }
    else if (b == 0 )
     {
      Firebase.setFloat("TuCoHang",1) ; 
     }
    else if (Firebase.failed())
    {
       mySerial.print("setting / number failed : ") ; 
       mySerial.println(Firebase.error() ) ;
       return ;
     } */
     
