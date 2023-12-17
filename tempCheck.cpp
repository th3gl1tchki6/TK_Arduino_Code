/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/tempCheck/src/tempCheck.ino"
#include "oled-wing-adafruit.h"

void setup();
void loop();
#line 3 "d:/tempCheck/src/tempCheck.ino"
OledWingAdafruit display;
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
void setup() {
display.setup();
display.clearDisplay();
}

void loop() {
display.loop();
display.clearDisplay();
uint64_t reading = analogRead(A4);
double voltage = (reading * 3.3) / 4095.0;
double temperatureC = (voltage - 0.5) * 100;
double temperatureF = (temperatureC * 1.8) + 32;
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.println(temperatureC);
display.setCursor(0,18);
display.println(temperatureF);
display.display();
delay(500);
}