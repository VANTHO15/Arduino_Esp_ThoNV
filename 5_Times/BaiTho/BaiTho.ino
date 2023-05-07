void setup()
{

  pinMode(7, OUTPUT);
  Serial.begin(9600);
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;
  TCCR1B |= 1 << CS12;
  TCNT1 = 3036;
  TIMSK1 = (1 << TOIE1);
  sei();
}

void loop()
{

}
ISR  (TIMER1_OVF_vect)
{
  TCNT1 = 3036;
  digitalWrite(7, !digitalRead(7));

}
