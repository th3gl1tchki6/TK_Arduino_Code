
#include <SparkFun_VCNL4040_Arduino_Library.h>
#include <oled-wing-adafruit.h>
#include <blynk.h>
#include <Wire.h>
VCNL4040 proximitySensor;
OledWingAdafruit display;
long startingProxValue = 0;
long deltaNeeded = 0;
boolean nothingThere = false;
void setup()
{
  Blynk.begin("QO2hgLDD59lVGic8wgPP5Bjq-Y22c8ix", IPAddress(167, 172, 234, 162), 8080);
  Serial.begin(9600);
  Wire.begin();
  display.setup();
  display.clearDisplay();
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  while (proximitySensor.begin() == false)
  {
    Serial.println("Device not found. Please check wiring.");
  }
  proximitySensor.powerOnProximity();
  proximitySensor.powerOnAmbient();
  proximitySensor.enableWhiteChannel();
}

void loop()
{
  Blynk.run();
  static bool Atoggle;
  static bool Btoggle;
  static bool Ctoggle;
  display.loop();
  display.clearDisplay();
  unsigned int proxValue = proximitySensor.getProximity();
  unsigned int ambientValue = proximitySensor.getAmbient();
  Serial.println(proxValue);
  bool Abutton = digitalRead(D4);
  bool Bbutton = digitalRead(D3);
  bool Cbutton = digitalRead(D2);
  Serial.println(Atoggle);
  if (Abutton == FALSE)
  {
    Atoggle = TRUE;
    Btoggle = FALSE;
    Ctoggle = FALSE;
  }
  if (Bbutton == FALSE)
  {
    Btoggle = TRUE;
    Atoggle = FALSE;
    Ctoggle = FALSE;
  }
  if (Cbutton == FALSE)
  {
    if (Ctoggle == FALSE)
    {
      Ctoggle = TRUE;
      Atoggle = FALSE;
      Btoggle = FALSE;
      delay(1000);
    }
    else
    {
      Ctoggle = FALSE;
      delay(1000);
    }
  }
  if (Ctoggle == TRUE)
  {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("ON BLYNK");
    display.display();
    Blynk.virtualWrite(V0, proxValue);
    Blynk.virtualWrite(V1, ambientValue);
  }
  else
  {
    if (Atoggle == TRUE)
    {
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println(proxValue);
      display.display();
    }
    else
    {
      if (Btoggle == TRUE)
      {
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.println(ambientValue);
        display.display();
      }
      else
      {
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.println("AWAITING INPUT");
        display.display();
      }
    }
  }
  if (proxValue < 10)
  {
    digitalWrite(D6, HIGH);
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
  }
  if (proxValue > 1000)
  {
    digitalWrite(D8, HIGH);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
  }
  if (proxValue > 10)
  {
    if (proxValue < 1000)
    {
      digitalWrite(D7, HIGH);
      digitalWrite(D6, LOW);
      digitalWrite(D8, LOW);
    }
  }
}