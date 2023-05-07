#include <LiquidCrystal.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define DT A0
#define CK A1
#define sw 9
LiquidCrystal_I2C lcd(0x27, 16, 2);
long sample = 0;
float val = 0;
long count = 0;

unsigned long readCount(void)
{
  unsigned long Count;
  unsigned char i;
  pinMode(DT, OUTPUT);
  digitalWrite(DT, HIGH);
  digitalWrite(A1, LOW);
  Count = 0;
  pinMode(DT, INPUT);
  while (digitalRead(DT));
  for (i = 0; i < 24; i++)
  {
    digitalWrite(A1, HIGH);
    Count = Count << 1;
    digitalWrite(A1, LOW);
    if (digitalRead(DT))
      Count++;
  }
  digitalWrite(A1, HIGH);
  Count = Count ^ 0x800000;
  digitalWrite(A1, LOW);
  return (Count);
}
void setup()
{
  pinMode(A1, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  lcd.print(" Weight ");
  lcd.setCursor(0, 1);
  lcd.print(" Measurement ");
  delay(1000);
  lcd.clear();
  calibrate();
}

void loop()
{
  count = readCount();
  int w = (((count - sample) / val) - 2 * ((count - sample) / val));
  lcd.setCursor(0, 0);
  lcd.print("Measured Weight");
  lcd.setCursor(0, 1);
  lcd.print(w);
  lcd.print("g ");

  if (digitalRead(sw) == 0)
  {
    val = 0;
    sample = 0;
    w = 0;
    count = 0;
    calibrate();
  }
}

void calibrate()
{
  lcd.clear();
  lcd.print("Calibrating...");
  lcd.setCursor(0, 1);
  lcd.print("Please Wait...");
  for (int i = 0; i < 100; i++)
  {
    count = readCount();
    sample += count;
  }
  sample /= 100;
  lcd.clear();
  lcd.print("Put 100g & wait");
  count = 0;
  while (count < 1000)
  {
    count = readCount();
    count = sample - count;
  }
  lcd.clear();
  lcd.print("Please Wait....");
  delay(2000);
  for (int i = 0; i < 100; i++)
  {
    count = readCount();
    val += sample - count;
  }
  val = val / 100.0;
  val = val / 100.0; // put here your calibrating weight
  lcd.clear();
}
