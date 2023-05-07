volatile byte dao = 1,a=0;
void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), tho, FALLING);

}
 
void loop() {
  digitalWrite(13,a%2);

}
void  tho()
{
  a=a+1;
}
