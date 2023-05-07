#include <avr/interrupt.h>
volatile int i= 0;
void setup()
{
    Serial.begin(9600);
    pinMode(7, OUTPUT);
    cli();                              
    
    /* Reset Timer/Counter1 */
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;       
    
    /* Setup Timer/Counter1 */
    TCCR1B |= (1 << CS11) | (1 << CS10);    // prescale = 64
    TCNT1 = 40536;
    TIMSK1 = (1 << TOIE1);                  // Overflow interrupt enable 
    sei();                                  // cho phép ngắt toàn cục
}
 
void loop()
{
    /* add main program code here */
}
 
 
ISR (TIMER1_OVF_vect) 
{
    TCNT1 = 40536;
    i++;
    Serial.println(i);
    digitalWrite(7, !digitalRead(7));
}
