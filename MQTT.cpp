/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/MQTT/src/MQTT.ino"
#include "oled-wing-adafruit.h"
#include <MQTT.h>
#include "blynk.h"
void setup();
void loop();
#line 4 "d:/MQTT/src/MQTT.ino"
SYSTEM_THREAD(ENABLED);
OledWingAdafruit display;
void callback(char *topic, byte *payload, unsigned int length);
MQTT client("lab.thewcl.com", 1883, callback);
void setup()
{
  Blynk.begin("0yOdKoftaOWWvlMqOtYKGhk81GzEOWYb", IPAddress(167, 172, 234, 162), 8080);
  pinMode(D7, OUTPUT);
  display.setup();
  display.clearDisplay();
  display.display();
}
void callback(char *topic, byte *payload, unsigned int length)
{
  
  display.loop();
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.printf("%s", p);
  Serial.println();
  int receivedInt = atoi(p);
  float receivedFloat = atof(p);
  int i;
  itoa(i, p, length);
  if (String(p).equals("1"))
  {
    digitalWrite(D7, HIGH);
  }
  else if (String(p).equals("0"))
  {
    digitalWrite(D7, LOW);
  }
  else
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(p);
    display.display();
    Serial.println("fuck");
  }
}
BLYNK_WRITE(V0) {
  String message = param.asStr();
  client.publish("twkessler", message);
}

void loop()
{
  Blynk.run();
  display.loop();
  client.subscribe("twkessler");
  if (client.isConnected())
  {
    client.loop();
  }
  else
  {
    client.connect(System.deviceID());
  }
  if (display.pressedA())
  {
    client.publish("twkessler", "A button pressed");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("A button has been pressed!");
    display.display();
  }
  if (display.pressedB())
  {
    client.publish("twkessler", "B button pressed");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("B button has been pressed!");
    display.display();
  }
  if (display.pressedC())
  {
    client.publish("twkessler", "C button pressed");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("C button has been pressed!");
    display.display();
  }
}
