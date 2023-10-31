#ifndef HomespanWiz
#define HomespanWiz
#include "WizLight.h"

struct HSWizLight : Service::LightBulb {
	WizLight* light;
	SpanCharacteristic* power;
	SpanCharacteristic* level;

	HSWizLight(char* ipAddr) : Service::LightBulb() {
		light = new WizLight(ipAddr);
		
		power = new Characteristic::On();
		level = new Characteristic::Brightness(100);
		level->setRange(0, 100, 1);
	}

	boolean update() {
		if (power->updated()) {
			if (power->getNewVal()) {
				light->On();
			}
			else {
				light->Off();
			}
		}

		if (level->updated()) {
			light->SetDim(level->getNewVal<int>());
		}

		return true;
	}
};

#endif // !HomespanWiz