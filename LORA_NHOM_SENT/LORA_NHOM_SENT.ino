//ARDUINO  E32 Module
//PIN 10  TX
//PIN 9 RX
//PIN 7  PIN M0
//PIN 8 PIN M1
//PIN 4 PIN AUX
//PIN 2  button Pin
//PIN 6 buzzer Pin
#include <UDOpenLora.h>
#include "DHT.h"

#define DHTPIN 3    
#define DHTTYPE DHT11   
#define M0_PIN 7
#define M1_PIN 8
#define AUX_PIN 4
#define lora_power TSMT_PWR_30DB

DHT dht(DHTPIN, DHTTYPE);
HardwareSerial* debugSerial = &Serial;;
SoftwareSerial LoraSerial(10,9);// RX, TX
UDOpenLora loraBoard(&LoraSerial);
/*--------------SENDER------------*/

int networkAddrH = 0x35;
int networkAddrL = 0x35;
int networkChanel = 0x19;
int deviceAddrH = 0x30; // 1 device : 1 addrH & addrL : receiver device address
int deviceAddrL = 0x30;
byte ADDR_H, ADDR_L;
char temp_t[10];
char humd_t[10];
char msg[16];
int length_t = 0;
float h = 0;
float t = 0;

void setup() {
  Serial.begin(9600); 
  dht.begin();
  LoraSerial.begin(9600);  
  loraBoard.setDebugPort(debugSerial);
  Serial.print("Configure Lora Module: ");
  loraBoard.setIOPin(M0_PIN, M1_PIN, AUX_PIN);
  delay(1000);
  loraBoard.LoraBegin((byte)(networkAddrH), (byte)(networkAddrL), (byte)(networkChanel), lora_power);
  Serial.println("GATE DONE");
}

void loop() {
  h =  50;//dht.readHumidity();             //read data
  t =  40;//dht.readTemperature();          //read data
  length_t = 0;
  length_t = String(h).length();
  String(h).toCharArray(humd_t,length_t);
  length_t=String(t).length();
  String(t).toCharArray(temp_t,length_t);
  strcpy(msg,"T");
  strcat(msg,temp_t);
  strcat(msg," H");
  strcat(msg,humd_t);
  loraBoard.SendMessage((byte)(deviceAddrH), (byte)(deviceAddrL),msg); //send message
  memset(msg,'\0',16);
  memset(temp_t,'\0',10);
  memset(humd_t,'\0',10);
  delay(5000);
}
