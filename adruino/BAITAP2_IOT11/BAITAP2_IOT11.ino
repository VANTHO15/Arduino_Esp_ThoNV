void setup()
{
Serial.begin(115200);
}

void loop()
{
 if(Serial.available())
    {
       String data = Serial.readString();
       Serial.println(data);
    }

}
