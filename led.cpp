#include "led.h"

led::led(Strip strip){
    //this is to get around the Fastled library using a template
    //dynamic memory for array of leds to set so each object can have its own without wasting memory.
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
    //setting the color from the colorInfo struct in led.h
    //if the brightness is set, let the setBrightness function handle it.
    if (colorInfo.brightness != 255) {
        return this->setBrightness(colorInfo.brightness);
    }
    //set the color with the struct
    for (int i = 0; i < numLeds; ++i) {
        leds[i] = CRGB(colorInfo.red, colorInfo.green, colorInfo.blue);
    }
    FastLED.show();
}

void led::setColor(unsigned int r, unsigned int g, unsigned int b) {
    //set the color based on rgb values passed in
    for (int i = 0; i < numLeds; ++i) {
        leds[i] = CRGB(r, g, b);
    }
    FastLED.show();
}

void led::setBrightness(unsigned int brightness) {
    //first set the brightness in the struct
    colorInfo.brightness = brightness;
    //make a multiplier based on the ratio between the set brightness and the max
    double multiplier = (double)brightness / MAX_BRIGHTNESS;
    //get new RGB values from the set colors multiplied by the brightness
    unsigned int red = lround(colorInfo.red * multiplier);
    unsigned int green = lround(colorInfo.green * multiplier);
    unsigned int blue = lround(colorInfo.blue * multiplier);
    //set the modified RGB values to the strip
    this->setColor(red, green, blue);
}

void led::turnOff() {
    //display all black on the strip
    for (int i = 0; i < numLeds; ++i) {
        leds[i] = CRGB(0,0,0);
    }
    FastLED.show();
}

void led::createRainbow() {
    //use fastleds build in rainbow generator
    fill_rainbow(leds, numLeds, gHue, 7);
    FastLED.show();
}

void led::update() {
    //for the patterns to animate
    EVERY_N_MILLISECONDS(20) {
        ++gHue;
        //FastLED.show();
    }
}