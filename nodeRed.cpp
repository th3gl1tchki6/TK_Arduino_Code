/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/nodeRed/src/nodeRed.ino"
#include "oled-wing-adafruit.h"
#include <MQTT.h>
void setup();
void loop();
#line 3 "d:/nodeRed/src/nodeRed.ino"
SYSTEM_THREAD(ENABLED);
OledWingAdafruit display;
void callback(char *topic, byte *payload, unsigned int length);
MQTT client("lab.thewcl.com", 1883, callback);
void setup()
{
  Serial.begin(10000);
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
  int receivedInt = atoi(p);
  float receivedFloat = atof(p);
  int i;
  itoa(i, p, length);
  Serial.println(p);
}

void loop()
{
  display.loop();
  uint16_t time = millis();
  static uint16_t check;
  client.subscribe("jimbus");
  client.subscribe("jumbus");
  if (client.isConnected())
  {
    client.loop();
    if (time == check)
    {
      client.publish("twkessler", "hehehehe");
      check = time + 10000;
    }
  }
  else
  {
    client.connect(System.deviceID());
    check = time;
  }
}
