#define LM35 analogRead(A7)
#include <TimerOne.h>
float tocdo;
unsigned long xung;
int mucdich = 3000;
float Kp = 0;
float Ki = 0.02;
float Kd = 0;
float K1 = 0.003;
float viphan = 0;
float tichphan = 0;
float e;
float pre_e;
float out;
int khoidong=0;
void setup() {
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(2, INPUT);
  Timer1.initialize(100000);
  Timer1.attachInterrupt(DO_TOC_DO);
  attachInterrupt(0, DEM_XUNG, FALLING);
  Serial.begin(250000);
}
void loop() {
}
void PID(float K) {
  pre_e = e;
  e = mucdich - tocdo;
  out += e * K;
  /*
  viphan = (e - pre_e) / 0.1;
  tichphan += e * 0.1;
  out = Kp * e + Ki * tichphan + Kd * viphan;
  */
  int PWM = (int)out;
  if (PWM > 255) {
    PWM = 255;
  }
  if (PWM < 0) {
    PWM = 0;
  }
  analogWrite(6, PWM);
  Serial.println(tocdo); 
  /*Serial.print("] [e: ");
  Serial.print(e); Serial.print("] [P: ");
  Serial.print(Kp * e); Serial.print("] [I: ");
  Serial.print(Ki * tichphan); Serial.print("] [D: ");
  Serial.print(Kd * viphan); Serial.print("] [out: ");
  Serial.print(out); Serial.println("]");
  */
}
void DO_TOC_DO() {
  tocdo = xung * 600 / 96;
  xung = 0;
  if(khoidong == 0 && tocdo < mucdich){
      out+=1;
      analogWrite(6,(int)out);
      Serial.println(tocdo);
    }
  else{
    khoidong =1;
  }
  if(khoidong == 1){
  PID(0.005);
  }
}
void DEM_XUNG() {
  xung++;
}
