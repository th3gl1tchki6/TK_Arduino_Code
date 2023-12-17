SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
void setup()
{
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}

void loop()
{
  analogWrite(D5, 255);
  analogWrite(D6, 0);
  analogWrite(D7, 0);
  delay(1000);
  analogWrite(D5, 0);
  analogWrite(D6, 255);
  delay(1000);
  analogWrite(D6, 0);
  analogWrite(D7, 255);
  delay(1000);
  analogWrite(D7, 0);
  analogWrite(D5, 255);
  analogWrite(D6, 50);
  delay(1000);
  analogWrite(D6, 90);
  analogWrite(D5, 255);
  analogWrite(D7, 0);
  delay(1000);
  analogWrite(D5, 255);
  analogWrite(D6, 0);
  analogWrite(D7, 255);
  delay(1000);
  analogWrite(D5, 0);
  analogWrite(D6, 140);
  analogWrite(D7, 200);
  delay(1000);
}