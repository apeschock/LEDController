#ifndef LEDCLASS
#define LEDCLASS

//need fastLED to control
#include <FastLED.h>

enum Strip { overhead, ambient, swing };



class led{
  public:
    led(Strip strip);
    ~led();
    void setColor();
    void setBrightness(unsigned int brightness);
    void createRainbow();
    struct colorParams_t {
        unsigned int hue = 0;
        unsigned int brightness = 20;
        unsigned int red = 0;
        unsigned int blue = 0;
        unsigned int green = 0;
    }colorInfo;

  private:
    //Need constants for FastLED library.
    static const EOrder colorOrder = GRB;
    static const LEDColorCorrection colorCorrect = TypicalSMD5050;
    static const int numLedOverhead = 10;
    static const int pinLedOverhead = 4;
    static const int numLedAmbient = 20;
    static const int pinLedAmbient = 16;
    static const int numLedSwing = 0;
    static const int pinLedSwing = 17;
    CRGB* leds;
    unsigned int numLeds;
};

#endif