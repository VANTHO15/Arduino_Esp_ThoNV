#include <Servo.h>
Servo sv1;
int s1 = 90; // lưu goc sv1
void setup()
{
  sv1.attach(A1);// sorvo1 nối vs chân A1.analog hay digital đều oke
  // sorvo quay ngay về goc 90
}               //khi lắp thì vị trí chờ của cơ cấu phải ứng vs 90

void loop()
{
  sv1.write(120);// goc muốn quayy đến .nó chỉ quay 1 lần như vâykj
  delay(1000);
  sv1.write(60);
  delay(1000);
}
