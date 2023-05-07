
void setup() 
{
  pinMode(6,OUTPUT); // Enable pin - chân khởi động - nối vào GND sẽ giúp ta bật động cơ bước, nối vô VCC động cơ bước được thả ra. Nôm na: GND = servo.attach, VCC = servo.detach
  pinMode(5,OUTPUT); // Step pin
  pinMode(4,OUTPUT); // Dir - pin
  digitalWrite(6,LOW); // Set Enable low
  digitalWrite(6,HIGH);
}

void loop() 
{
   // Đặt Enable ở trạng thái LOW
  digitalWrite(4,LOW); // Đặt Dir  ở trạng thái HIGH
  //Serial.println("Cho chay 200 steps (1 vong)");
  for (int i=0; i<=350;i++){
    digitalWrite(5,HIGH); // Output high
    delayMicroseconds(1000); // chờ
    digitalWrite(5,LOW); // Output low
    delayMicroseconds(1000); // chờ
  }
  delay(10000);
  digitalWrite(6,LOW); // Đặt Dir  ở trạng thái HIGH
}
