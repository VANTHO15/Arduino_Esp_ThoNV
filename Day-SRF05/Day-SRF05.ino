#define TRIG A4
#define ECHO A3
void setup() 
{
 Serial.begin(9600);
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);
  // đo thời gian mức cao ở chân       pulseIn(chan,HIGH)    dơn vị là muycrogiay
}
long tg=0;
void loop()
{
  if(millis()-tg>1000)
  {
  Serial.println(KC());
      tg=millis();
  }

}

uint8_t KC()
{
  long long thoigian;
  digitalWrite(TRIG,1);  // tao xung đẻ bao hieu hoat đọng
  delayMicroseconds(5);
  digitalWrite(TRIG,0);
  thoigian=pulseIn(ECHO,HIGH);
  uint8_t khoangcach=thoigian/(2*29.412);
  return khoangcach;
}
