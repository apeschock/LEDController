#ifndef LEDManager
#define LEDManager
#include "led.h"
#include "BlynkSimpleEsp32Fixed.h"

class LedManager {
private:
public:
	LedManager();
	led over = led(overhead);
	led amb = led(ambient);
	led swing = led(swingable);
	void update();
};

#endif