#include <Arduino_FreeRTOS.h>
#include <queue.h>
QueueHandle_t integerQueue;
void setup() {
  integerQueue = xQueueCreate(10, // Queue length
                              sizeof(int) // Queue item size
                             );

  if (integerQueue != NULL)
  {
    xTaskCreate(TaskSerial,
                "Serial",
                128,
                NULL,
                2,
                NULL);
    xTaskCreate(TaskAnalogRead,
                "AnalogRead",
                128,
                NULL,
                1,
                NULL);

  }

  xTaskCreate(TaskBlink,
              "Blink",
              128,
              NULL,
              0,
              NULL );
}
void loop() {}
void TaskAnalogRead(void *pvParameters)
{
  (void) pvParameters;

  for (;;)
  {
    int sensorValue = 10;//analogRead(A0);
    xQueueSend(integerQueue, &sensorValue, portMAX_DELAY);
    vTaskDelay(1);
  }
}
void TaskSerial(void * pvParameters) {
  (void) pvParameters;
  Serial.begin(9600);
  while (!Serial)
  {
    vTaskDelay(1);
  }
  int valueFromQueue = 0;
  for (;;)
  {
    if (xQueueReceive(integerQueue, &valueFromQueue, portMAX_DELAY) == pdPASS)
    {
      Serial.println(valueFromQueue);
    }
  }
}
void TaskBlink(void *pvParameters)
{
  (void) pvParameters;
  pinMode(8, OUTPUT);
  for (;;)
  {
    digitalWrite(8, HIGH);
    vTaskDelay( 250 / portTICK_PERIOD_MS );
    digitalWrite(8, LOW);
    vTaskDelay( 250 / portTICK_PERIOD_MS );
  }
}
