#include <AccelStepper.h>
#define dirPin 22
#define stepPin 23
#define motorInterfaceType 1
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
void setup()
{
  stepper.setMaxSpeed(1000);
}
void loop() { 
  stepper.setCurrentPosition(0);
  while(stepper.currentPosition() != 1600)
  {
    stepper.setSpeed(800);
    stepper.runSpeed();
  }
  while(stepper.currentPosition() != 0) 
  {
    stepper.setSpeed(-200);
    stepper.runSpeed();
  }
  delay(1000);
}
