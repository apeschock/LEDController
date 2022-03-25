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
    void rainbow();
    void rainbowGlitter();
    void confetti();
    void sinelon();
    void juggle();
    void bpm();
    void update();
    void switchPower(bool power);
    struct colorParams_t {
        bool powerState = false;
        unsigned int brightness = 255;
        unsigned int red = 255;
        unsigned int blue = 255;
        unsigned int green = 255;
    }colorInfo;
    unsigned int currentPattern = 0; 

  private:
    //Need constants for FastLED library.
    static const EOrder colorOrder = GRB;
    static const LEDColorCorrection colorCorrect = TypicalSMD5050;
    const int MAX_BRIGHTNESS = 255;
    static const int numLedOverhead = 87;
    static const int pinLedOverhead = 4;
    static const int numLedAmbient = 20;
    static const int pinLedAmbient = 16;
    static const int numLedSwing = 20;
    static const int pinLedSwing = 17;
    typedef void (led::*patternList)();
    patternList patterns[6] = {&led::rainbow, &led::rainbowGlitter, &led::confetti,
        &led::sinelon, &led::juggle, &led::bpm};
    uint8_t gHue = 0;
    CRGB* leds;
    unsigned int numLeds;
};

#endif