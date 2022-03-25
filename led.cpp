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
    case swingable:
        leds = new CRGB[numLedSwing];
        numLeds = numLedSwing;
        FastLED.addLeds<WS2812B, pinLedSwing, colorOrder>(leds, numLedSwing).setCorrection(colorCorrect);
    }
}

led::~led() {
    delete[] leds;
}

void led::setColor() {
    //only if powerSwitch is on
    if (!colorInfo.powerState) {
        return;
    }
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

void led::switchPower(bool power) {
    //set the saved power state
    colorInfo.powerState = power;
    if (power) {
        //this must be called for the brightness slider to have affect.
        setBrightness(colorInfo.brightness);
    }
    else {
        //display all black on the strip
        for (int i = 0; i < numLeds; ++i) {
            leds[i] = CRGB(0, 0, 0);
        }
        FastLED.show();
    }
}

void led::setBrightness(unsigned int brightness) {
    //first set the brightness in the struct
    colorInfo.brightness = brightness;
    //return out if the powerSwitch is off
    if (!colorInfo.powerState || currentPattern) {
        return;
    }
    //make a multiplier based on the ratio between the set brightness and the max
    double multiplier = (double)brightness / MAX_BRIGHTNESS;
    //get new RGB values from the set colors multiplied by the brightness
    unsigned int red = lround(colorInfo.red * multiplier);
    unsigned int green = lround(colorInfo.green * multiplier);
    unsigned int blue = lround(colorInfo.blue * multiplier);
    //set the modified RGB values to the strip
    this->setColor(red, green, blue);
}

void led::rainbow() {
    fill_rainbow(leds, numLeds, gHue, 15);
}

void led::rainbowGlitter() {
    rainbow();
    if (random8() < 70) {
        leds[random16(numLeds)] += CRGB::White;
    }
}

void led::confetti() {
    fadeToBlackBy(leds, numLeds, 10);
    int pos = random16(numLeds);
    leds[pos] += CHSV(gHue + random8(64), 200, 255);
}

void led::sinelon() {
    fadeToBlackBy(leds, numLeds, 20);
    int pos = beatsin16(13, 0, numLeds - 1);
    leds[pos] += CHSV(gHue, 255, 192);
}

void led::juggle() {
    fadeToBlackBy(leds, numLeds, 20);
    uint8_t dothue = 0;
    for (int i = 0; i < 8; i++) {
        leds[beatsin16(i + 7, 0, numLeds - 1)] |= CHSV(dothue, 200, 255);
        dothue += 32;
    }
}

void led::bpm() {
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    for (int i = 0; i < numLeds; i++) {
        leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    }
}

void led::slowFadeTo(unsigned int desiredBrightness) {
    while (desiredBrightness < colorInfo.brightness) {
        fadeToBlackBy(leds, numLeds, 1);
        colorInfo.brightness -= 1;
        FastLED.delay(5);
    }
    FastLED.show();
}

void led::update() {
    //if no pattern or power then return out
    if (!currentPattern || !colorInfo.powerState) {
        return;
    }
    //for the patterns to animate
    EVERY_N_MILLISECONDS(15) {
        ++gHue;
    }
    (this->*patterns[currentPattern -1])();
    if (colorInfo.brightness != MAX_BRIGHTNESS) {
        fadeToBlackBy(leds, numLeds, MAX_BRIGHTNESS - colorInfo.brightness);
    }
    FastLED.show();
    FastLED.delay(1000 / 120);
}