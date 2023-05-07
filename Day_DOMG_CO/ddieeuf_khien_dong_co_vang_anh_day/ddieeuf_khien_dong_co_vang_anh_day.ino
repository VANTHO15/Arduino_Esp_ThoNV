void setup() {
  pinMode(4,OUTPUT); // 4 là đigital thôi
  pinMode(5,OUTPUT);// analog đk 1 động cơ
}

void loop() {
 digitalWrite(4,0); // tieen 
 analogWrite(5,7);// 7 laf tu 0.255

  digitalWrite(4,1); // tieen 
 analogWrite(5,255-7);// 7 laf tu 0.255
}
