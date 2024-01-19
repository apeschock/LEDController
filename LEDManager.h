#ifndef LEDManager
#define LEDManager
//#include "BlynkSimpleEsp32Fixed.h"
#include "led.h"

class LedManager {
private:
public:
	LedManager();
	led over = led(overhead);
	led amb = led(ambient);
	led swing = led(swingable);
	void updatePattern();
	void loading();
	void connected();
};
#endif