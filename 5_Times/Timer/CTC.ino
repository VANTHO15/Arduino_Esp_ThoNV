#include <avr/interrupt.h>

 
void setup()
{
    pinMode(13, OUTPUT);
    cli();              // tắt ngắt toàn cục
    
    /* Reset Timer/Counter1 */
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
    
    /* Setup Timer/Counter1 */
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10); // prescale = 64 and CTC mode 4
    OCR1A = 1000;              // initialize OCR1A
    TIMSK1 = (1 << OCIE1A);     // Output Compare Interrupt Enable Timer/Counter1 channel A
    sei();                      // cho phép ngắt toàn cục
}
 
void loop()
{
    /* add main program code here */
}
    
 
ISR (TIMER1_COMPA_vect) 
{
    digitalWrite(13, !digitalRead(13));
}
