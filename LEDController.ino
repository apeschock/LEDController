#include "BlynkCredentials.h"
#include "LEDManager.h"
#include <EEPROM.h>

LedManager ledmanager = LedManager();


void setup()
{
    // Debug console
    Serial.begin(115200);
    EEPROM.begin(512);
    
    BlynkStart();
}

void loop()
{
    //over.createRainbow();
    Blynk.run();
}