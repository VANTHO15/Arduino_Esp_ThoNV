unsigned long time;
void setup()
{
    // khởi tạo giá trị biến time là giá trị hiện tại
    // của hàm millis();
    
    pinMode(13, OUTPUT);
    digitalWrite(13, 1);
    pinMode(10,INPUT_PULLUP);
}

void loop() 
{
    if(digitalRead(10)==0)
    {
      time=millis();
      if(millis()-time > 1000)
      digitalWrite(13,!digitalRead(13));
    }
    time=millis();
}
