#include <AccelStepper.h>
#define dirPin 22
#define stepPin 23
#define motorInterfaceType 1
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
void setup() {
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);
}
void loop() {
  stepper.moveTo(1600);
  stepper.runToPosition();
  delay(1000);
  stepper.moveTo(0);
  stepper.runToPosition();
  delay(1000);
}
