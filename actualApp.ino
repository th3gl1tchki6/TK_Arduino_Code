SYSTEM_THREAD(ENABLED);
#include <blynk.h>
bool value = FALSE;
void setup() 
{
  Serial.begin(9600);
  Blynk.begin("9xVQdlyZEUR91QYEiNZ9-PAgldvD5uP_", IPAddress(167, 172, 234, 162), 8080);
}

void loop() 
{

  Blynk.run();
  if (value == TRUE) 
  {
    Serial.println(value);
  }
}
BLYNK_WRITE(V0)
{   
  if (value == TRUE) 
  {
    value = FALSE;
  } 
  else
  {
    value = TRUE;
  }
}