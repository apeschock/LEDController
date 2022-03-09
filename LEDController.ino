#include "BlynkCredentials.h"
#include "LEDManager.h"

//make a global led manager to access the leds from anywhere.
LedManager ledmanager = LedManager();


void setup()
{
    // Debug console
    Serial.begin(115200);
    
    //launch the blynk service
    BlynkStart();
}

void loop()
{
    ledmanager.update();

    //get updates from blynk and remain connected.
    Blynk.run();
}