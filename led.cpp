#include "led.h"

led::led(Strip strip){
    switch (strip) {
    case overhead:
        leds = new CRGB[numLedOverhead];
        numLeds = numLedOverhead;
        FastLED.addLeds<WS2812B, pinLedOverhead, colorOrder>(leds, numLedOverhead).setCorrection(colorCorrect);
        break;
    case ambient:
        leds = new CRGB[numLedAmbient];
        numLeds = numLedAmbient;
        FastLED.addLeds<WS2812B, pinLedAmbient, colorOrder>(leds, numLedAmbient).setCorrection(colorCorrect);
        break;
    case swing:
        leds = new CRGB[numLedSwing];
        numLeds = numLedSwing;
        FastLED.addLeds<WS2812B, pinLedSwing, colorOrder>(leds, numLedSwing).setCorrection(colorCorrect);
    }
}

led::~led() {
    delete[] leds;
}

void led::setColor() {
    for (int i = 0; i < numLeds; ++i) {
        leds[i] = CRGB(colorInfo.red, colorInfo.green, colorInfo.blue);
    }
    Serial.println("Red " + (String)leds->r);
    Serial.println("Green " + (String)leds->g);
    Serial.println("Blue " + (String)leds->b);
    FastLED.show();
}

void led::setBrightness(unsigned int brightness) {
    
}

void led::createRainbow() {
    uint8_t thisHue = beat8(10, 255);
    fill_rainbow(leds, 300, 10, 10);
    FastLED.show();
}