#ifndef BLYNKCONTROL
#define BLYNKCONTROL
#include "BlynkCredentials.h"

#define BLYNK_PRINT Serial

//use the blynk header that was fixed
#include "BlynkSimpleEsp32Fixed.h"


class BlynkStart {
public:
	BlynkStart() {
		//start blynk with the auth token.
		char auth[] = BLYNK_AUTH_TOKEN;
		Blynk.begin(auth);
	}
	static bool confirmBlynkConnection() {
		if (!Blynk.connected()) {
			return Blynk.connect();
		}
		return true;
	}
};

#endif // !BLYNKCONTROL