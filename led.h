#ifndef LEDCLASS
#define LEDCLASS

//need fastLED to control
#define FASTLED_INTERNAL
#include <FastLED.h>
struct colorParams_t {
    bool powerState = false;
    unsigned int brightness = 255;
    unsigned int red = 255;
    unsigned int blue = 255;
    unsigned int green = 255;
};

struct blynkPins_t {
    int power;
    int brightness;
    int redPin;
    int greenPin;
    int bluePin;
};

enum Strip { overhead, ambient, swingable };
enum Source { None, BlynkServ, HomeSpan };

class led{
  public:
    led(Strip strip);
    ~led();
    CRGB* getLeds();
    int getNumLeds();
    void setColor();
    void setColor(unsigned int r, unsigned int g, unsigned int b);
    void setColorAndSave(unsigned int r, unsigned int g, unsigned int b);
    void setBrightness(unsigned int brightness);
    void rainbow();
    void rainbowGlitter();
    void confetti();
    void sinelon();
    void juggle();
    void bpm();
    void slowFadeTo(unsigned int desiredBrightness);
    void updatePattern();
    void incHue();
    void switchPower(bool power);
    colorParams_t colorInfo;
    unsigned int currentPattern = 0;
    Strip getCurrentType();
    void setHomespanCallback(std::function<void(colorParams_t)> HomespanCallback);
    //void setBlynkConnection(BlynkWifi* BlynkConn);
    Source LastModifyingService = None;
    void setBlynkPins(int power, int bright, int red, int green, int blue);

  private:
    //Need constants for FastLED library.
    static const EOrder colorOrder = GRB;
    static const LEDColorCorrection colorCorrect = TypicalSMD5050;
    const int MAX_BRIGHTNESS = 255;
    //Constants for LedAmounts and Pins
    static const int numLedOverhead = 107;
    static const int pinLedOverhead = 4;
    static const int numLedAmbient = 84;
    static const int pinLedAmbient = 16;
    static const int numLedSwing = 20;
    static const int pinLedSwing = 17;
    typedef void (led::*patternList)();
    patternList patterns[6] = {&led::rainbow, &led::rainbowGlitter, &led::confetti,
        &led::sinelon, &led::juggle, &led::bpm};
    uint8_t gHue = 0;
    CRGB* leds;
    unsigned int numLeds;
    Strip currentType;
    std::function<void(colorParams_t)> homespanCallback;
    //BlynkWifi* blynkConn;
    void updateExternalGuis();
    blynkPins_t blynkPins;
    void writeBlynkData();
};

#endif