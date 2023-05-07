#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <Keypad.h>
const byte ROWS = 4; // Bốn hàng
const byte COLS = 4; // Ba cột
char keys[ROWS][COLS] = 
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
byte rowPins[ROWS] = {5, 6, 7, 8};
byte colPins[COLS] = {9, 10, 11, 12};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Servo myServo;

char STR[4] = {'3', '0', '0', '5'}; // Cài đặt mật khẩu tùy ý
char str[4] = {' ', ' ', ' ', ' '};
int i, j, count = 0;

void setup() {
  myServo.attach(4); // Khai báo chân điều khiển động cơ
  lcd.init();        // Khai báo sử dụng LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.print(" Enter Password");
}

void loop() {
  char key = keypad.getKey();

  if (key) // Nhập mật khẩu
  {
    if (i == 0) {
      str[0] = key;
      lcd.setCursor(6, 1);
      lcd.print(str[0]);
      delay(1000); // Ký tự hiển thị trên màn hình LCD trong 1s
      lcd.setCursor(6, 1);
      lcd.print("*"); // Ký tự được che bởi dấu *
    }
    if (i == 1) {
      str[1] = key;
      lcd.setCursor(7, 1);
      lcd.print(str[1]);
      delay(1000);
      lcd.setCursor(7, 1);
      lcd.print("*");
    }
    if (i == 2) {
      str[2] = key;
      lcd.setCursor(8, 1);
      lcd.print(str[2]);
      delay(1000);
      lcd.setCursor(8, 1);
      lcd.print("*");
    }
    if (i == 3) {
      str[3] = key;
      lcd.setCursor(9, 1);
      lcd.print(str[3]);
      delay(1000);
      lcd.setCursor(9, 1);
      lcd.print("*");
      count = 1;
    }
    i = i + 1;
  }

  if (count == 1)
  {
    if (str[0] == STR[0] && str[1] == STR[1] && str[2] == STR[2] &&
        str[3] == STR[3])
    {
      lcd.clear();
      lcd.print("   Thanh Cong ^_^!!");
      delay(3000);
      myServo.write(180); // Mở cửa
      lcd.clear();
      lcd.print("      Opened!");
      i = 0;
      count = 0;
    }
    else
    {
      lcd.clear();
      lcd.print("  Sai Roi ^_^!!");
      delay(3000);
      lcd.clear();
      lcd.print(" Try Again :((");
      delay(3000);
      lcd.clear();
      lcd.print(" Enter Password");
      i = 0;
      count = 0;
    }
  }
  switch (key)
  {
    case '*':
      lcd.clear();
      myServo.write(90); //Đóng cửa
      lcd.print("     Closed!");
      delay(10000);
      lcd.clear();
      lcd.print(" Enter Password");
      i = 0;
      break;
  }
}
