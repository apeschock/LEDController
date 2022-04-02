#include "LEDManager.h"

BlynkWifi Blynk(_blynkTransport);
bool synced = false;

//this is to refernce the led objects from the blynk functions
namespace internLeds {
	LedManager* pThis;
}
LedManager::LedManager() {
	internLeds::pThis = this;
}

//call update for these 2 strands for patterns to work.
void LedManager::update() {
	over.update();
	if (synced) {
		for (int i = 0; i < amb.getNumLeds(); ++i) {
			amb.getLeds()[i] = over.getLeds()[i];
		}
		FastLED.show();
		return;
	}
	amb.update();
}

//show status during loading and successful connection
void LedManager::loading() {
	//fading in without messing with the class
	for (int i = 0; i < 50; ++i) {
		over.setColor(i, 0, 0);
		FastLED.delay(8);
	}
	over.setColor(50, 0, 0);
}

void LedManager::connected() {
	over.setColor(0, 0, 50);
	//fading out but without screwing up the current data in the class.
	for (int i = 50; i >= 0; --i) {
		over.setColor(0, 0, i);
		FastLED.delay(10);
	}
}

//external blynk methods that get called when theres a change.
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
	internLeds::pThis->over.slowFadeTo(param.asInt());
}

extern BLYNK_WRITE(V4) {
	internLeds::pThis->over.switchPower(param.asInt());
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
	internLeds::pThis->amb.slowFadeTo(param.asInt());
}

extern BLYNK_WRITE(V9) {
	internLeds::pThis->amb.switchPower(param.asInt());
}

extern BLYNK_WRITE(V10) {
	internLeds::pThis->swing.colorInfo.red = param.asInt();
	internLeds::pThis->swing.setColor();
}

extern BLYNK_WRITE(V11) {
	internLeds::pThis->swing.colorInfo.green = param.asInt();
	internLeds::pThis->swing.setColor();
}

extern BLYNK_WRITE(V12) {
	internLeds::pThis->swing.colorInfo.blue = param.asInt();
	internLeds::pThis->swing.setColor();
}

extern BLYNK_WRITE(V13) {
	internLeds::pThis->swing.slowFadeTo(param.asInt());
}

extern BLYNK_WRITE(V14) {
	internLeds::pThis->swing.switchPower(param.asInt());
}

extern BLYNK_WRITE(V15) {
	if (param.asInt()) {
		Blynk.virtualWrite(V17, internLeds::pThis->over.currentPattern);
		synced = true;
	}
	else {
		synced = false;
	}
}

extern BLYNK_WRITE(V16) {
	internLeds::pThis->over.currentPattern = param.asInt();
	if (synced) {
		Blynk.virtualWrite(V17, internLeds::pThis->over.currentPattern);
		internLeds::pThis->amb.currentPattern = param.asInt();
	}
	if (param.asInt() == 0) {
		internLeds::pThis->over.setColor();
	}
}

extern BLYNK_WRITE(V17) {
	if (synced) {
		Blynk.virtualWrite(V17, internLeds::pThis->over.currentPattern);
		return;
	}
	internLeds::pThis->amb.currentPattern = param.asInt();
	if (param.asInt() == 0) {
		internLeds::pThis->amb.setColor();
	}
}

extern BLYNK_WRITE(V18) {
	ESP.restart();
}


extern BLYNK_CONNECTED() {
	//set blynk to mirror what the controller is set to on start up
	//mostly to verify data is the same across the service and mcu.
	Blynk.virtualWrite(V0, internLeds::pThis->over.colorInfo.red);
	Blynk.virtualWrite(V1, internLeds::pThis->over.colorInfo.green);
	Blynk.virtualWrite(V2, internLeds::pThis->over.colorInfo.blue);
	Blynk.virtualWrite(V3, internLeds::pThis->over.colorInfo.brightness);
	Blynk.virtualWrite(V4, internLeds::pThis->over.colorInfo.powerState);
	Blynk.virtualWrite(V5, internLeds::pThis->amb.colorInfo.red);
	Blynk.virtualWrite(V6, internLeds::pThis->amb.colorInfo.green);
	Blynk.virtualWrite(V7, internLeds::pThis->amb.colorInfo.blue);
	Blynk.virtualWrite(V8, internLeds::pThis->amb.colorInfo.brightness);
	Blynk.virtualWrite(V9, internLeds::pThis->amb.colorInfo.powerState);
	Blynk.virtualWrite(V10, internLeds::pThis->swing.colorInfo.red);
	Blynk.virtualWrite(V11, internLeds::pThis->swing.colorInfo.green);
	Blynk.virtualWrite(V12, internLeds::pThis->swing.colorInfo.blue);
	Blynk.virtualWrite(V13, internLeds::pThis->swing.colorInfo.brightness);
	Blynk.virtualWrite(V14, internLeds::pThis->swing.colorInfo.powerState);
	Blynk.virtualWrite(V15, synced);
	Blynk.virtualWrite(V16, internLeds::pThis->over.currentPattern);
	Blynk.virtualWrite(V17, internLeds::pThis->amb.currentPattern);
	Blynk.virtualWrite(V18, 0); //reset off
}