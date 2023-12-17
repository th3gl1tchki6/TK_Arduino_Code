SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

void setup()
{
  pinMode(D7, INPUT);
  pinMode(D5, OUTPUT);
}

void loop()
{ 
  bool value = digitalRead(D7);
  if (value == TRUE)
  {
    digitalWrite(D5, HIGH);
  }
  else
  {
    digitalWrite(D5, LOW);
  }
}