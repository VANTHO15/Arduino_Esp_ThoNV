#include <SoftwareSerial.h>
#include <UDOpenLora.h>

HardwareSerial* debugSerial = &Serial;
SoftwareSerial LoraSerial(10, 9); // RX, TX
UDOpenLora loraBoard(&LoraSerial);

#define lora_power TSMT_PWR_30DB
byte DeviceLoraAddr_H = 0x30;
byte DeviceLoraAddr_L = 0x30;
byte LoraChanel = 0x19;
byte destADDR_H = 0x35;
byte destADDR_L = 0x35;
byte SourceAddr_H, SourceAddr_L;
char data_buf[128];
uint8_t data_len;
char Mess[128] = "Hello! I'm UDOpenLora Receiver";
String Temp = "";
String Humd = "";
#define M0_PIN 7
#define M1_PIN 8
#define AUX_PIN 4

/*-------RECEIVER---------*/
void setup()
{
  Serial.begin(9600);
  LoraSerial.begin(9600);
  loraBoard.setDebugPort(debugSerial);
  pinMode(2, OUTPUT);
  Serial.print("Configure Lora Module: ");
  loraBoard.setIOPin(M0_PIN, M1_PIN, AUX_PIN);
  delay(1000);
  if (loraBoard.LoraBegin(DeviceLoraAddr_H, DeviceLoraAddr_L, LoraChanel, lora_power))
  {
    Serial.println("Configure ERROR!");
  }
  Serial.println("Configure Lora Module DONE!");
  loraBoard.SendMessage(destADDR_H, destADDR_L, Mess);
}

void loop()
{
  if (loraBoard.ReceiveMsg(&SourceAddr_H, &SourceAddr_L, data_buf, &data_len) == RET_SUCCESS)
  { 
    Serial.println();
    Serial.print("Msg from: 0x");
    Serial.print(SourceAddr_H, HEX);
    Serial.println(SourceAddr_L, HEX);
    Serial.print("Message length:");
    Serial.println(data_len);
    Serial.print("Receive Message:");
    Serial.println(data_buf);
    for (int i = 0; i < data_len; i++)
    {
      if (data_buf[i] == 'T')
      {
        for (int j = 1; j < data_len; j++)
        {
          if (data_buf[j] == 'H')
          {
            for (int k = j; k < data_len; k++)
            {
              Humd += data_buf[k + 1];
            }
            break;
          }
          Temp += data_buf[j];
        }
      }
    }
    Serial.print("Temp=");
    Serial.println(Temp);
    Serial.print("Humd=");
    Serial.print(Humd);
    float Humd_f = Humd.toInt();
    if (Humd_f)
    {
      digitalWrite(2, ! digitalRead(2));   
    }
    Temp = "";
    Humd = "";
  }
}
