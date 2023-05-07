//step moter bằng biến trở
const int stepPin = 3;
const int dirPin = 4; 
int ReadAnalog,TimeDelay;
void setup() {
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  digitalWrite(dirPin,HIGH);
}
void loop() {
  TimeDelay = GetValueByFunc(); 
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(TimeDelay);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(TimeDelay);
}
int GetValueByFunc() {
  int ReadAnalog = analogRead(A0); 
  int Value = map(ReadAnalog, 0, 1023, 300,4000); // chuyển value (0,1023)->(300,4000)
  return Value;  
}
