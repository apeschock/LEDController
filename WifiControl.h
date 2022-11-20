#ifndef WIFICONTROL
#define WIFICONTROL

#include <WiFiManager.h>
#include <WiFi.h>
#include <WiFiClient.h>

class WifiControl {
public:
	void startWifi() {
		wifi.autoConnect("ESP");
	}

	void checkConnection() {
		//check if wifi is connected
		if (wifi.getWLStatusString() == "WL_CONNECTED") {
			//restart the blynk service if we disconnected
			if (!blynkStarted) {
				BlynkStart();
				blynkStarted = true;
			}
		}
		else {
			//
			blynkStarted = false;
			wifi.setConfigPortalTimeout(120);
			wifi.autoConnect("ESP");
		}
	}

private:
	WiFiManager wifi;
	boolean blynkStarted = true;
};

#endif // !WIFICONTROL