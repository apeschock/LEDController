#include "led.h"

led::led(Strip strip){
    switch (strip) {
    case overhead:
        leds = new CRGB[numLedOverhead];
        FastLED.addLeds<WS2812B, pinLedOverhead, colorOrder>(leds, numLedOverhead).setCorrection(colorCorrect);
        break;
    case ambient:
        leds = new CRGB[numLedAmbient];
        FastLED.addLeds<WS2812B, pinLedAmbient, colorOrder>(leds, numLedAmbient).setCorrection(colorCorrect);
        break;
    case swing:
        leds = new CRGB[numLedSwing];
        FastLED.addLeds<WS2812B, pinLedSwing, colorOrder>(leds, numLedSwing).setCorrection(colorCorrect);
    }
}

void led::setColor(unsigned int r, unsigned int g, unsigned int b) {

}

void led::setBrightness(unsigned int brightness) {

}

void led::createRainbow() {
    uint8_t thisHue = beat8(10, 255);
    fill_rainbow(leds, 300, 10, 10);
    FastLED.show();
}