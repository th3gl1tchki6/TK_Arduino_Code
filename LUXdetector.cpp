/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/LUXdetector/src/LUXdetector.ino"
void setup();
void loop();
#line 1 "d:/LUXdetector/src/LUXdetector.ino"
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
uint16_t maximum = 0;
uint16_t minimum = 9000;
uint16_t light = 0;
void setup()
{
  pinMode(D5, OUTPUT);
}

void loop()
{
  uint16_t value = analogRead(A5);
  maximum = max(value, maximum);
  minimum = min(value, minimum);
  Serial.println(maximum);
  Serial.println(minimum);
  light = map(value, minimum, maximum, 0, 255);
  analogWrite(D5, light);
  Serial.println(light);
}