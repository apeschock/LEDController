#ifndef WizLightSetup
#define WizLightSetup
#include "HomeSpanWiz.h"

void setupWizLights() {
	new SpanAccessory();
		new Service::AccessoryInformation();
			new Characteristic::Identify();
			new Characteristic::Name("Bedroom Light");
		new HSWizLight("10.0.0.31");
}

#endif // !WizLightSetup