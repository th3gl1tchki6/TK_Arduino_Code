/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/Potentiometer/src/Potentiometer.ino"


void setup();
void loop();
#line 3 "d:/Potentiometer/src/Potentiometer.ino"
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
void setup() {
pinMode(D5, OUTPUT);
Serial.begin(9600);
}

void loop() {
uint16_t value = analogRead(A5);
Serial.println(value);
digitalWrite(D5, HIGH);
delay(value);
uint16_t valueB = analogRead(A5);
digitalWrite(D5, LOW);
delay(valueB);
}