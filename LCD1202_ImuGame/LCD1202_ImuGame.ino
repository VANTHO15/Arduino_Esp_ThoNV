#include <EEPROM.h>
#include <Wire.h>
#include "lcd1202.h"

Lcd1202 display(2, 0, 4, 5); 

char str[32];

float roll;
float pitch;
int centerX = 48;
int centerY = 32;
float posX = centerX;
float posY = centerY;
int targetX;
int targetY;
int score = 0;
long start_time;
int high_score;

#define MPU 0x68
 
#define A_R 16384.0 // 32768/2
#define G_R 131.0 // 32768/250

#define RAD_A_DEG = 57.295779

int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

float Acc[2];
float Gy[3];
float Angle[3];


void setup()
{
  Serial.begin(115200);
  EEPROM.begin(512);
  display.init();
  display.clear();
  display.display();

  display.setColor(BLACK);

  Wire.begin(D7,D6); // SDA,SCL
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  setRandom();

  high_score = EEPROM.read(0);
  drawIntroGame();

  delay(500);
}

void loop()
{
  getIMU();
  drawIMUgame();

  Serial.print(roll);
  Serial.print("\t");
  Serial.println(pitch);
  delay(100);
}

void getIMU() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,6,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  
  Acc[1] = atan(-1*(AcX/A_R)/sqrt(pow((AcY/A_R),2) + pow((AcZ/A_R),2)))*RAD_TO_DEG;
  Acc[0] = atan((AcY/A_R)/sqrt(pow((AcX/A_R),2) + pow((AcZ/A_R),2)))*RAD_TO_DEG;

  pitch = Acc[0];
  roll = -Acc[1];
}

void setRandom() {
  targetX = random(38, 92);  // border is 67 and 126
  targetY = random(4, 60);    // border is 1 and 62
}

void drawIntroGame() {  
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(8, 25, "IMU GAME");
  display.display();
  delay(500);
}

void drawIMUgame() {
  display.clear();

  display.setFont(ArialMT_Plain_10);
  
  display.drawRect(34, 0, 62, 64);
  
  display.drawRect(targetX - 2, targetY - 2, 4, 4);
    
  posX -= roll / 5;
  posY += pitch / 5;
  posX = constrain(posX, 36, 93);
  posY = constrain(posY, 2, 61);
  display.fillCircle(posX, posY, 2);

  if (posX > (targetX - 2) && posX < (targetX + 2) && posY > (targetY - 2) && posY < (targetY + 2)) {
    score++;
    setRandom();
  }

  if (score > high_score) {
    high_score = score;
    EEPROM.write(0, high_score);
    EEPROM.commit();
  }
  
  display.drawString(4, 0, "Score");
  sprintf(str, "%d", score);
  display.drawString(4, 10, str);
  
  display.drawString(0, 30, "High");
  display.drawString(0, 40, "Score");
  sprintf(str, "%d", high_score);
  display.drawString(4, 50, str);
  
  display.display();
  
  if (posX == 36 || posX == 93 || posY == 2 || posY == 61) {                         // HIT BORDER = GAME OVER
    display.setColor(WHITE);
    display.fillRect(35, 1, 60, 62);
    display.setColor(BLACK);
    display.drawString(38, 10, "Game Over");
    display.drawString(37, 30, "Reset");
    display.drawString(60, 40, "to start");
    display.display();
    while (1) {                                                               // while wait for reset
      delay(50);
    }
  }
}
