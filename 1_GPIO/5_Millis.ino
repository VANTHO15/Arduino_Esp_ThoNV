byte led1 = 8;
byte led2 = 9;
unsigned long time1 = 0;
unsigned long time2 = 0;

void setup()
{
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
}

void loop()
{
    if ( (unsigned long) (millis() - time1) > 1000 )
    {
        if ( digitalRead(led1) == LOW )
        {
            digitalWrite(led1, HIGH);
        } else {
            digitalWrite(led1, LOW );
        }
        time1 = millis();
    }
    
    if ( (unsigned long) (millis() - time2) > 300  )
    {
        if ( digitalRead(led2) == LOW )
        {
            digitalWrite(led2, HIGH);
        } else {
            digitalWrite(led2, LOW );
        }
        time2 = millis();
    }
}
