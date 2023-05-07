#include <EEPROM.h>

int a = 0;
int value;

void setup()
{
  Serial.begin(9600);
  EEPROM.write(0,500);
   int a=EEPROM.read(0); 
  int b=EEPROM.read(1);
  Serial.println(a);
  Serial.print(b);
}

void loop()
{
/*  value = EEPROM.read(a);

  Serial.print(a);
  Serial.print("\t");
  Serial.print(value);
  Serial.println();

  a = a + 1;

  if (a ==1023)
    a = 0;

  delay(50);*/
}
