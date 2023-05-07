void setup() {
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop(){
int n=analogRead(A0);
if(n>200) digitalWrite(3,1); else digitalWrite(3,0);
if(n>400) digitalWrite(4,1); else digitalWrite(4,0);
if(n>600) digitalWrite(5,1);  else digitalWrite(5,0);
if(n>800) digitalWrite(6,1); else digitalWrite(6,0);
}
