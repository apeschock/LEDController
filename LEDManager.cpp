#include "LEDManager.h"

BlynkWifi Blynk(_blynkTransport);

namespace internLeds {
	LedManager* pThis;
}

LedManager::LedManager() {
	internLeds::pThis = this;
}


void LedManager::update() {
	over.update();
	amb.update();
}

extern BLYNK_WRITE(V0) {
	internLeds::pThis->over.colorInfo.red = param.asInt();
	internLeds::pThis->over.setColor();
}

extern BLYNK_WRITE(V1) {
	internLeds::pThis->over.colorInfo.green = param.asInt();
	internLeds::pThis->over.setColor();
}

extern BLYNK_WRITE(V2) {
	internLeds::pThis->over.colorInfo.blue = param.asInt();
	internLeds::pThis->over.setColor();
}

extern BLYNK_WRITE(V3) {
	internLeds::pThis->over.setBrightness(param.asInt());
}

extern BLYNK_WRITE(V4) {
	switch (param.asInt()) {
	case 0:
		internLeds::pThis->over.turnOff();
		break;
	case 1:
		internLeds::pThis->over.setColor();
		break;
	}
}

extern BLYNK_WRITE(V5) {
	internLeds::pThis->amb.colorInfo.red = param.asInt();
	internLeds::pThis->amb.setColor();
}

extern BLYNK_WRITE(V6) {
	internLeds::pThis->amb.colorInfo.green = param.asInt();
	internLeds::pThis->amb.setColor();
}

extern BLYNK_WRITE(V7) {
	internLeds::pThis->amb.colorInfo.blue = param.asInt();
	internLeds::pThis->amb.setColor();
}

extern BLYNK_WRITE(V8) {
	internLeds::pThis->amb.setBrightness(param.asInt());
}

extern BLYNK_WRITE(V9) {
	switch (param.asInt()) {
	case 0:
		internLeds::pThis->amb.turnOff();
		break;
	case 1:
		internLeds::pThis->amb.setColor();
		break;
	}
}

extern BLYNK_WRITE(V10) {
	internLeds::pThis->swing.colorInfo.blue = param.asInt();
	internLeds::pThis->swing.setColor();
}

extern BLYNK_WRITE(V11) {
	internLeds::pThis->swing.colorInfo.blue = param.asInt();
	internLeds::pThis->swing.setColor();
}

extern BLYNK_WRITE(V12) {
	internLeds::pThis->swing.colorInfo.blue = param.asInt();
	internLeds::pThis->swing.setColor();
}

extern BLYNK_WRITE(V13) {
	internLeds::pThis->swing.setBrightness(param.asInt());
}

extern BLYNK_WRITE(V14) {
	switch (param.asInt()) {
	case 0:
		internLeds::pThis->swing.turnOff();
		break;
	case 1:
		internLeds::pThis->swing.setColor();
		break;
	}
}

extern BLYNK_WRITE(V15) {

}

extern BLYNK_WRITE(V16) {
	switch (param.asInt()) {
	case 0:

		break;
	case 1:
		internLeds::pThis->over.createRainbow();
		break;
	case 2:

		break;
	}
}