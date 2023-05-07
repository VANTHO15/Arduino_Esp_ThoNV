#include <LiquidCrystal.h>
#define RS 8
#define E 9
#define D4 10
#define D5 11
#define D6 12
#define D7 13
int x;
LiquidCrystal lcd(RS,E,D4,D5,D6,D7); 
void setup() {
pinMode(2,INPUT_PULLUP);
pinMode(3,INPUT_PULLUP);
lcd.begin(16,2);
lcd.setCursor(0, 0);
lcd.print("CAI DAT : ");
}

void loop() {
if(digitalRead(2)==0){
   x++;
   while(digitalRead(2)==0){}
}
if(digitalRead(3)==0){
   x--;
   while(digitalRead(3)==0){}
}
lcd.setCursor(5, 1);
if(x<10) lcd.print(" ");
if(x<100) lcd.print(" ");
if(x<0) x=0;
lcd.print(x);
chaychay(x);
}
void chaychay(int k){
  if(k>=1){if(millis()%1500<600){
    lcd.setCursor(3,1);
    lcd.print(">  ");
    
  }
  if(millis()%1500>600&&millis()%1500<1200){
    lcd.setCursor(3,1);
    lcd.print(">>>");
    
  }}
}
