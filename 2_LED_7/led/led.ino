void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
}
int a=1;
void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(13,!a);
delay(1000);
}
