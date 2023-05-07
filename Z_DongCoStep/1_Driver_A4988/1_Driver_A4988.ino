// Arduino và driver A4988
const int stepPin = 23; 
const int dirPin = 22; 
void setup() {
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}
void loop() {
  digitalWrite(dirPin,HIGH); // cho động cơ đi theo một hướng cụ thể
  for(int x = 0; x < 1600; x++) {  // tạo 200 xung để đc 1 vòng quay
    digitalWrite(stepPin,HIGH); 
    delay(5);
    digitalWrite(stepPin,LOW); 
    delay(5);
  }
  delay(1000); 
  
  digitalWrite(dirPin,HIGH); //Thay đỏi chiều
  for(int x = 0; x < 1600; x++) { // tạo 400 xung quay 2 vòng
    digitalWrite(stepPin,HIGH);
   delay(5);
    digitalWrite(stepPin,LOW);
   delay(5);
  }
  delay(1000);
}
