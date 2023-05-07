#include <Arduino_FreeRTOS.h>
#include <semphr.h>
SemaphoreHandle_t interruptSemaphore;
void setup() {
  pinMode(2, INPUT_PULLUP);
  xTaskCreate(TaskLed, 
              "Led", 
              128, 
              NULL,
              0, 
              NULL );
  interruptSemaphore = xSemaphoreCreateBinary();
  if (interruptSemaphore != NULL) {
    attachInterrupt(digitalPinToInterrupt(2), interruptHandler, RISING);
  }
}
void loop() {}
void interruptHandler()
{
  xSemaphoreGiveFromISR(interruptSemaphore, NULL);
}

void TaskLed(void *pvParameters)
{
  (void) pvParameters;

  pinMode(8, OUTPUT);

  for (;;)
  {
    if (xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdPASS)
    {
      digitalWrite(8, !digitalRead(8));
    }

  }
}
