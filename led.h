#ifndef LEDCLASS
#define LEDCLASS

//need fastLED to control
#include <FastLED.h>
#include "BlynkSimpleEsp32Fixed.h"
enum Strip{overhead, ambient, swing};

static struct colorParams_t {
    unsigned int hue = 0;
    unsigned int brightness = 20;
    unsigned int red = 0;
    unsigned int blue = 0;
    unsigned int green = 0;
}colorParams_over, colorParams_amb, colorParams_swing;

class led{
  public:
    led(Strip strip);
    void setColor(unsigned int r, unsigned int g, unsigned int b);
    void setBrightness(unsigned int brightness);
    void createRainbow();

  private:
    //Need constants for FastLED library.
    static const EOrder colorOrder = GRB;
    static const LEDColorCorrection colorCorrect = TypicalSMD5050;
    static const int numLedOverhead = 300;
    static const int pinLedOverhead = 4;
    static const int numLedAmbient = 0;
    static const int pinLedAmbient = 16;
    static const int numLedSwing = 0;
    static const int pinLedSwing = 17;
    CRGB* leds;
};

#endif