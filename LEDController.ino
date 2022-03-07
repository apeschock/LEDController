#include "BlynkCredentials.h"
#include "LEDManager.h"

LedManager ledmanager = LedManager();


void setup()
{
    // Debug console
    Serial.begin(115200);
    Serial.print("Here");
    Serial.flush();
    
    BlynkStart();
}

void loop()
{
    //ledmanager.update();

    Blynk.run();
}