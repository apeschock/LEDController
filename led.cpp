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
    FastLED.show();
}

void led::setColor(unsigned int r, unsigned int g, unsigned int b) {
    for (int i = 0; i < numLeds; ++i) {
        leds[i] = CRGB(r, g, b);
    }
    FastLED.show();
}

void led::setBrightness(unsigned int brightness) {
    double multiplier = (double)brightness / MAX_BRIGHTNESS;
    colorInfo.brightness = brightness;
    unsigned int red = lround(colorInfo.red * multiplier);
    unsigned int green = lround(colorInfo.green * multiplier);
    unsigned int blue = lround(colorInfo.blue * multiplier);
    this->setColor(red, green, blue);
}

void led::turnOff() {
    for (int i = 0; i < numLeds; ++i) {
        leds[i] = CRGB(0,0,0);
    }
    FastLED.show();
}

void led::createRainbow() {
    fill_rainbow(leds, numLeds, gHue, 7);
    FastLED.show();
}

void led::update() {
    EVERY_N_MILLISECONDS(20) {
        ++gHue;
        //FastLED.show();
    }
}