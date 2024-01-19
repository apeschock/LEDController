#ifndef HomeSpanLed
#define HomeSpanLed

struct HSLed : Service::LightBulb {
	led* Led;
	const float RANGE_ADJUST = 2.55;
	const float MAX_VAL_U8 = 255.0;
	const float PERCENTCONV = 100.0;
	SpanCharacteristic* power;
	SpanCharacteristic* H;
	SpanCharacteristic* S;
	SpanCharacteristic* V;

	HSLed(led* ledRef) : Service::LightBulb() {
		Led = ledRef;
		power = new Characteristic::On();
		H = new Characteristic::Hue(0);
		S = new Characteristic::Saturation(0);
		V = new Characteristic::Brightness(100);
		V->setRange(0, 100, 2);
		ledRef->setHomespanCallback(std::bind(&HSLed::updateExternal, this, std::placeholders::_1));
	}

	boolean update() {
		float v, h, s, r, g, b;
		boolean updateColor = false;
		//set current values before update
		h = H->getVal<float>();
		s = S->getVal<float>();
		v = V->getVal<float>();

		if (power->updated()) {
			Led->switchPower(power->getNewVal() ? true : false);
			Led->LastModifyingService = HomeSpan;
		}

		if (H->updated()) {
			h = H->getNewVal<float>();
			updateColor = true;
		}

		if (S->updated()) {
			s = S->getNewVal<float>();
			updateColor = true;
		}

		if (V->updated()) {
			v = V->getNewVal<float>();
			Led->slowFadeTo(lround(v * RANGE_ADJUST));
			Led->LastModifyingService = HomeSpan;
		}

		if (updateColor) {
			LedPin::HSVtoRGB(h, s/100.0, 100.0, &r, &g, &b);
			Led->LastModifyingService = HomeSpan;

			Led->setColorAndSave(lround(r * RANGE_ADJUST), lround(g * RANGE_ADJUST), lround(b * RANGE_ADJUST));
			Led->slowFadeTo(lround(v * RANGE_ADJUST));
		}
		
		return (true);
	}

	void updateExternal(colorParams_t currentState) {
		power->setVal(currentState.powerState);
		V->setVal((currentState.brightness/MAX_VAL_U8)*(PERCENTCONV));
	}
};

#endif HomeSpanLed