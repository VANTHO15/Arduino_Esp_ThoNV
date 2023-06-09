#include <SoftwareSerial.h>
SoftwareSerial mySerial(11,10);
void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
}


void loop()
{
  if (Serial.available() > 0)
    switch (Serial.read())
    {
      case 's':
        SendMessage();
        break;
      case 'r':
        RecieveMessage();
        break;
    }

  if (mySerial.available() > 0)
  {
    Serial.write(mySerial.read());
  }
}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+84782439973\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("help me");// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
void RecieveMessage()
{
  delay(1000);
}
