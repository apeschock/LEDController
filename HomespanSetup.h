#ifndef HomespanSetup
#define HomespanSetup
#include "HomeSpanLed.h"

void setupHomespan(LedManager* ledManager) {
	//setup HomeSpan for Homekit integration
	homeSpan.begin(Category::Lighting, "EspLights");
	new SpanAccessory();
		new Service::AccessoryInformation();
			new Characteristic::Identify();
			new Characteristic::Name("Overhead");
		new HSLed(&ledManager->over);

	new SpanAccessory();
		new Service::AccessoryInformation();
			new Characteristic::Identify();
			new Characteristic::Name("Ambient");
		new HSLed(&ledManager->amb);
}


#endif //HomespanSetup