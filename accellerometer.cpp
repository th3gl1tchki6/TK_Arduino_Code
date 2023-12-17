/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#line 1 "d:/accellerometer/src/accellerometer.ino"
#include "Particle.h"

#include "LIS3DH.h"
#include "oled-wing-adafruit.h"
void setup();
void loop();
#line 5 "d:/accellerometer/src/accellerometer.ino"
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);
const unsigned long PRINT_SAMPLE_PERIOD = 100;
LIS3DHSPI accel(SPI, D3, WKP);
OledWingAdafruit display;
unsigned long lastPrintSample = 0;

void setup() {
	Serial.begin(9600);
	display.setup();

	display.clearDisplay();
	display.display();
	delay(5000);
	LIS3DHConfig config;
	config.setAccelMode(LIS3DH::RATE_100_HZ);

	bool setupSuccess = accel.setup(config);
	Serial.printlnf("setupSuccess=%d", setupSuccess);
}

void loop() {
display.loop();
	if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD) {
		lastPrintSample = millis();

		LIS3DHSample sample;
		if (accel.getSample(sample)) {
		Serial.printlnf("%d,%d,%d", sample.x + 600, sample.y + 900, sample.z - 15750);
		display.clearDisplay();
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(0,0);
		display.println(sample.x + 605);
		display.display();
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(0,9);
		display.println(sample.y + 925);
		display.display();
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(0,18);
		display.println(sample.z - 15785);
		display.display();
		delay(500);
		}
		else {
			Serial.println("no sample");
		}
	}
}


