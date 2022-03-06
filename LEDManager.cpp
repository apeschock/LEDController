#include "LEDManager.h"

BlynkWifi Blynk(_blynkTransport);

namespace internLeds {
	LedManager* pThis;
}

LedManager::LedManager() {
	internLeds::pThis = this;
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

}

extern BLYNK_WRITE(V4) {

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

}

extern BLYNK_WRITE(V9) {

}

extern BLYNK_WRITE(V10) {

}

extern BLYNK_WRITE(V11) {

}

extern BLYNK_WRITE(V12) {

}

extern BLYNK_WRITE(V13) {

}

extern BLYNK_WRITE(V14) {

}

extern BLYNK_WRITE(V15) {

}

extern BLYNK_WRITE(V16) {

}