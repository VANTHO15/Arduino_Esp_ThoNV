//http://www.arduino.cc/playground/uploads/Code/Password.zip
#include <Password.h>
//http://www.arduino.cc/playground/uploads/Code/Keypad.zip
#include <Keypad.h> 

Password password = Password( "0512" );

const byte ROWS = 4; // Four rows
const byte COLS = 4; //  columns

int holdDelay = 700; //Thời gian trễ để xem là nhấn 1 nút nhằm tránh nhiễu
int n = 3; // 
int state = 0; //nếu state =0 ko nhấn,state =1 nhấn thời gian nhỏ , state = 2 nhấn giữ lâu
char key = 0;

// Define the Keymap
char keys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 5,6,7,8 };// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 9,10,11,12 };


// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define ledPin 4

void setup(){
 
 digitalWrite(ledPin, LOW);   // sets the LED off
 Serial.begin(9600);
 keypad.addEventListener(keypadEvent); //add an event listener for this keypad
}
 
void loop(){
 //keypad.getKey();
 char temp = keypad.getKey();
 
  if ((int)keypad.getState() ==  PRESSED) {
    if (temp != 0) {
      key = temp;
    }
  }
  if ((int)keypad.getState() ==  HOLD) {
    state++;
    state = constrain(state, 1, n-1);
    delay(holdDelay);
  }
 
  if ((int)keypad.getState() ==  RELEASED) {
    key += state;
    state = 0;
    //Xuất lên Máy tính để xem kết quả
    Serial.println(key);
 
  }
  delay(100);
}


//take care of some special events

void keypadEvent(KeypadEvent eKey){
 switch (keypad.getState()){
   case PRESSED:
     Serial.print("Pressed: ");
     Serial.println(eKey);
     switch (eKey){
       case '*': guessPassword(); break;
       case '#': password.reset(); break;
        default: 
              password.append(eKey);
    }
 }
}

void guessPassword(){
    Serial.print("Guessing password... ");
    if (password.evaluate()){
          digitalWrite(ledPin,HIGH);
          Serial.print("correct\n");
    }else{
          digitalWrite(ledPin,LOW);
          Serial.print("incorrect\n");
    }
}
