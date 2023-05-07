//TB6600  nguồn 24-36v

#include <AccelStepper.h>
#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1   // kiểu là 1
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
void setup() {
   // Đặt tốc độ và gia tốc tối đa:
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
}
void loop() {
  // Đặt vị trí đích:
  stepper.moveTo(8000);
    // Chạy đến vị trí mục tiêu với tốc độ đã đặt và tăng / giảm tốc:
  stepper.runToPosition();
  delay(1000);
   // Chuyển về 0:
  stepper.moveTo(0);
  stepper.runToPosition();
  delay(1000);
}
