#include <Arduino_FreeRTOS.h>
int loa = 10;
int ledDelay = 50;
int redPin = 5;
int bluePin = 6;
int potpin = A0; //Định nghĩa chân quang trở chân 0
int val = 0; // giá trị ban đầu
int thoigian, khoangcach;
unsigned long time1 = 0;
unsigned long time2 = 0;
void setup()
{ Serial.begin(9600);
  Serial.println(F("In Setup function"));
  pinMode(12, OUTPUT);
  pinMode(11, INPUT);
  pinMode(loa, OUTPUT);
  pinMode(redPin, OUTPUT); //pinMode đèn đỏ là OUTPUT
  pinMode(bluePin, OUTPUT); //pinMode đèn xanh là OUTPUT
  xTaskCreate(MyTask1, "Task1", 100, NULL, 0, NULL);
  xTaskCreate(MyTask2, "Task2", 100, NULL, 1, NULL);
}
void loop()
{
}
static void MyTask1(void* pvParameters)
{ while (1)

  {
    digitalWrite(12, HIGH);
    delayMicroseconds(1000);
    digitalWrite(12, LOW);
    thoigian = pulseIn(11, HIGH);
    khoangcach = 0.0344 * (thoigian / 2);
    Serial.print(khoangcach);
    Serial.println("cm");



    if (khoangcach < 160) {
      digitalWrite(loa, HIGH);
      delay(20);
      digitalWrite(loa, LOW);
    }
    else {
      digitalWrite(loa, LOW);
    }
    Serial.println(F("Task1"));
    vTaskDelay(110 / portTICK_PERIOD_MS);
  }
}

//Similarly this is task 2

static void MyTask2(void* pvParameters)

{ while (1)

  { Serial.println(val);
    val = analogRead(potpin);
    if ( val < 95) {
      if ( (unsigned long) (millis() - time1) > 100 )
      {
        if ( digitalRead(redPin) == LOW )
        {
          digitalWrite(redPin, HIGH);
        } else {
          digitalWrite(redPin, LOW );
        }
        time1 = millis();
      }

      if ( (unsigned long) (millis() - time2) > 50  )
      {
        if ( digitalRead(bluePin) == LOW )
        {
          digitalWrite(bluePin, HIGH);
        } else {
          digitalWrite(bluePin, LOW );
        }
        time2 = millis();

      }



    } else {
      digitalWrite(redPin, LOW );
      digitalWrite(bluePin, LOW );
    }
    Serial.println(F("Task2"));
    vTaskDelay(150 / portTICK_PERIOD_MS);
    delay(500);
  }
}
