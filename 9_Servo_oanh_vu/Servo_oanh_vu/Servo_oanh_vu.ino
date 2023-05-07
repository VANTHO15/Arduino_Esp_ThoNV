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
  SERVOR(180, 5);
  SERVOR(0, 2);
  SERVOR(60, 30);
  SERVOR(120, 1);
}
void SERVOR(int goc, int dly)
{
  if (goc > s1)
    for (s1, s1 <= goc; S1++)
    {
      sv1.write(s1);
      delay(dly);
    }
  else
    for (s1; s1 >= goc; s1--)
    {
      sv1.write(s1);
      delay(dly);
    }
}
