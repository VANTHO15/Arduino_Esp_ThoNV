void setup() {
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
}

void loop()
{
  for(int i=100;i<255;i++)
  {
    analogWrite(5,i);
    delay(10);
  }
  for(int i=255;i>100;i--)
  {
    analogWrite(5,i);
    delay(10);
  }
 

}
