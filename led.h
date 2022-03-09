#ifndef LEDCLASS
#define LEDCLASS

//need fastLED to control
#include <FastLED.h>

enum Strip { overhead, ambient, swingable };

class led{
  public:
    led(Strip strip);
    ~led();
    void setColor();
    void setColor(unsigned int r, unsigned int g, unsigned int b);
    void setBrightness(unsigned int brightness);
    void createRainbow();
    void update();
    void turnOff();
    struct colorParams_t {
        unsigned int hue = 0;
        unsigned int brightness = 255;
        unsigned int red = 255;
        unsigned int blue = 255;
        unsigned int green = 255;
    }colorInfo;

  private:
    //Need constants for FastLED library.
    static const EOrder colorOrder = GRB;
    static const LEDColorCorrection colorCorrect = TypicalSMD5050;
    const int MAX_BRIGHTNESS = 255;
    static const int numLedOverhead = 3;
    static const int pinLedOverhead = 4;
    static const int numLedAmbient = 20;
    static const int pinLedAmbient = 16;
    static const int numLedSwing = 20;
    static const int pinLedSwing = 17;
    uint8_t gHue = 0;
    CRGB* leds;
    unsigned int numLeds;
};

#endif