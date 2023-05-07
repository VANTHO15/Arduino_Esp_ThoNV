#include "Keypad.h"
 
//Bạn có thể tham khảo thêm tại: https://github.com/Chris--A/Keypad/blob/master/examples/HelloKeypad/HelloKeypad.ino
 
const byte rows = 4; //số hàng
const byte columns = 4; //số cột
int n = 3; // 
int state = 0; //nếu state =0 ko nhấn,state =1 nhấn thời gian nhỏ , state = 2 nhấn giữ lâu
char key = 0;
char keys[rows][columns] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
byte rowPins[rows] = {5, 6, 7, 8}; 
byte columnPins[columns] = {9, 10, 11, 12};
//cài đặt thư viện keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);
void setup() {
  Serial.begin(9600);
 
}
void loop() {  
  char temp = keypad.getKey();
  if ((int)keypad.getState() ==  PRESSED)
  {
    if (temp != 0)
      key = temp;
  }
  if ((int)keypad.getState() ==  HOLD)
  {
    state++;
    state = constrain(state, 1, n-1);
    delay(700);
  }
  if ((int)keypad.getState() ==  RELEASED) 
  {
    key += state;
    state = 0;
    //Xuất lên Máy tính để xem kết quả
    Serial.println(key);
 
  }
  delay(100);
}
