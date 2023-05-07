#define DT A0
#define SCK A1
long sample = 0;
float val = 0;
long count = 0;
unsigned long readCount(void)
{
  unsigned long Count;
  unsigned char i;
  pinMode(DT, OUTPUT);
  digitalWrite(DT, HIGH);
  digitalWrite(SCK, LOW);
  Count = 0;
  pinMode(DT, INPUT);
  while (digitalRead(DT));
  for (i = 0; i < 24; i++)
  {
    digitalWrite(SCK, HIGH);
    Count = Count << 1;
    digitalWrite(SCK, LOW);
    if (digitalRead(DT))
      Count++;
  }
  digitalWrite(SCK, HIGH);
  Count = Count ^ 0x800000;
  digitalWrite(SCK, LOW);
  return (Count);
}

void setup()
{
  Serial.begin(9600);
  pinMode(SCK, OUTPUT);
  calibrate();
}

void loop()
{
  count = readCount();
  int w = (((count - sample) / val) - 2 * ((count - sample) / val));
  Serial.print("g");
  Serial.print(w);
  Serial.println();
}
void calibrate()
{
  Serial.print("Calibrating...");
  Serial.println("Please Wait...");
  for (int i = 0; i < 100; i++)
  {
    count = readCount();
    sample += count;
  }
  sample /= 100;

  Serial.print("Put 100g & wait");
  count = 0;
  while (count < 1000)
  {
    count = readCount();
    count = sample - count;
  }

  Serial.println("Please Wait....");
  delay(2000);
  for (int i = 0; i < 100; i++)
  {
    count = readCount();
    val += sample - count;
  }
  val = val / 100.0;
  val = val / 100.0; // put here your calibrating weight
}
