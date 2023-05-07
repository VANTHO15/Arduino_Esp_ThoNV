#include <Arduino_FreeRTOS.h>

void TaskSo1( void *pvParameters );
void TaskSo2( void *pvParameters );

void setup() {

  Serial.begin(9600);

  xTaskCreate(
    TaskSo1
    ,  "So1"
    ,  128 // ram sử dụng >=64 byte
    ,  NULL
    ,  2  // mức độ ưu tiên
    ,  NULL );

  xTaskCreate(
    TaskSo2
    ,  "So2"
    ,  128
    ,  NULL
    ,  1
    ,  NULL );

}

void loop()
{

}
void TaskSo1( void *pvParameters  )
{
  
  while (1)
  {
    Serial.println("Task1");
    //vTaskDelay (1000 / portTICK_PERIOD_MS);  // thời gian bị chặn lại là 1.5 giây
  }
}

void TaskSo2( void *pvParameters )
{
 
  while (1)
  {
    Serial.println("Task2");
    //vTaskDelay (2000 / portTICK_PERIOD_MS);
  }
}
