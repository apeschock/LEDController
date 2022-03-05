#include "BlynkCredentials.h"
#include "led.h"
#include "BlynkInterface.h"

led over(overhead);
led amb(ambient);
led lamp(swing);

void setup()
{
    // Debug console
    Serial.begin(115200);
    
    BlynkStart();
}

void loop()
{
    over.createRainbow();
    Blynk.run();
}