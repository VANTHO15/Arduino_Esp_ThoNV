#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2); 
void setup()
{
  lcd.init();                    
  lcd.backlight();
  lcd.setCursor(2,0);
  lcd.print("Arduinokit.vn");
  lcd.setCursor(0,1);
  lcd.print("Xin chao cac ban");
}

void loop()
{
}
