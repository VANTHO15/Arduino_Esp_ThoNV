void setup() {
  Serial.begin(9600);
}
char data[15];
int i = 0;
void loop()
{
  if (Serial.available())
  {
    char kt = Serial.read();
    if ((kt != 'j') && (kt != 'J'))
    {
      data[i] = kt;
      i++;
    }
    else
    {
      if (i == 0)
        Serial.println("Chua nhap gi ca!");
      else
        for (int j = 0; j < i; j++)
          Serial.print(data[j]);
    }
  }
}
