#include <functional>
//#include "BlynkControl.h"
#include "LEDManager.h"
#include "HomespanSetup.h"
//#include "WifiControl.h"

//make a global led manager to access the leds from anywhere.
LedManager ledmanager = LedManager();
//WifiControl wifi;

void setup()
{
    // Debug console
    Serial.begin(115200);

    //set the 
    FastLED.clear();

    //show loading on the leds
    ledmanager.loading();
    
    //start the wifi service
    //wifi.startWifi();

    //launch the blynk service
    //BlynkStart();

    //getting here means blynk has connected
    ledmanager.connected();

    //setup homespan (HomespanSetup.h)
    setupHomespan(&ledmanager);

}

void loop() 
{
    //Call an update everytime so that patterns will animate
    //ledmanager.updatePattern();
    
    //reconnect to wifi if the connection is lost
    //wifi.checkConnection();
    //BlynkStart::confirmBlynkConnection();

    //get updates from blynk and remain connected.
    //Blynk.run();
    
    //Homespan run
    homeSpan.poll();
}