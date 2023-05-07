void setup() {

  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);
}
int a = 0,k=0;
void loop()
{
  a++;k=k+200;
  delay(k);
  if (a == 1)
    digitalWrite(4, ! digitalRead(4));
  if (a == 2)
    digitalWrite(5, !digitalRead(5));
  if (a == 3)
    digitalWrite(6, !digitalRead(6));
  if (a == 4)
    digitalWrite(7, !digitalRead(7));
  if (a == 5) a = 0;
  if(k==800) k=1;

}
