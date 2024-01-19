#ifndef HomespanSetup
#define HomespanSetup
#include <HomeSpan.h>
#include "HomeSpanLed.h"

HSLed* over;
HSLed* amb;
const long DELAY_TIME = 1 * 60 * 1000UL;
static long lastTime = 0;

void setupHomespan(LedManager* ledManager) {
	//setup HomeSpan for Homekit integration
	homeSpan.begin(Category::Lighting, "EspLights");
	new SpanAccessory();
		new Service::AccessoryInformation();
			new Characteristic::Identify();
			new Characteristic::Name("Overhead");
		over = new HSLed(&ledManager->over);

	new SpanAccessory();
		new Service::AccessoryInformation();
			new Characteristic::Identify();
			new Characteristic::Name("Ambient");
		amb = new HSLed(&ledManager->amb);
}

#endif //HomespanSetup