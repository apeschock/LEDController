#include "BlynkCredentials.h"
#include "LEDManager.h"

//make a global led manager to access the leds from anywhere.
LedManager ledmanager = LedManager();


void setup()
{
    // Debug console
    Serial.begin(115200);

    //set the 
    FastLED.clear();

    //show loading on the leds
    ledmanager.loading();
    
    //launch the blynk service
    BlynkStart();

    //getting here means blynk has connected
    ledmanager.connected();
}

void loop()
{
    ledmanager.update();

    //get updates from blynk and remain connected.
    Blynk.run();
}