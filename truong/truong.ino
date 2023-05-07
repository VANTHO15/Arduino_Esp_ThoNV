void setup() {
  pinMode(7,INPUT_PULLUP);
  pinMode(13,OUTPUT);

}

void loop() {

int nut=digitalRead(7);
if(nut==1) digitalWrite(13,0);
else       digitalWrite(13,1);
}
