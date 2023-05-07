void setup() {

Serial.begin(9600);
pinMode(13,OUTPUT);
}

void loop() {
String sau;
if(Serial.available())
{
  sau=Serial.readString();
  if(sau.indexOf("bat")!=-1)  digitalWrite(13,1);
  else                         digitalWrite(13,0);
}
}
