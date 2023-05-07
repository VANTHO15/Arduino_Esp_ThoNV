#define LM35 analogRead(A7)
#include <TimerOne.h>
float ndo;
int mucdich = 60;
float Kp = 9;
float Ki = 0.05;
float Kd = 0.03;
float viphan = 0;
float tichphan = 0;
float e;
float pre_e;
float out;
void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A3, OUTPUT);
  Serial.begin(250000);
  Timer1.initialize(100000);
  Timer1.attachInterrupt(PID);
}
void loop() {
  //PID_CUIBAP(70);
}
void PID_CUIBAP(int setndo) {
  ndo = LM35 * 5.0 / 1023 * 100;
  if (millis() % 500 < 2) {
    Serial.println(ndo);
  }
  if (ndo < setndo) {
    analogWrite(5, 255);
    digitalWrite(A3,1);
    //Serial.println("   [ON]");
  }
  if (ndo >= setndo) {
    analogWrite(5, 0);
    digitalWrite(A3,0);
    //Serial.println("   [OFF]");
  }
}
void PID() {
  ndo = LM35 * 5.0 / 1023 * 100;
  pre_e = e;
  e = mucdich - ndo;
  //if (pre_e > 0 && e <= 0) { tichphan = 0; }
  viphan = (e - pre_e) / 0.1;
  tichphan += e * 0.1;
  out = Kp * e + Ki * tichphan + Kd * viphan;
  int PWM = (int)out;
  if (PWM > 255) {
    PWM = 255;
  }
  if (PWM < 0) {
    PWM = 0;
  }
  analogWrite(5, PWM);
  Serial.print(ndo); Serial.print("] [e: ");
  Serial.print(e); Serial.print("] [P: ");
  Serial.print(Kp * e); Serial.print("] [I: ");
  Serial.print(Ki * tichphan); Serial.print("] [D: ");
  Serial.print(Kd * viphan); Serial.print("] [out: ");
  Serial.print(out); Serial.println("]");
}
