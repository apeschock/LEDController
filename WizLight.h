#ifndef WIZLIGHT
#define WIZLIGHT

#include <WiFi.h>
#include <WiFiUdp.h>

class WizLight {
private:
    WiFiUDP udp;
    const int udpPort = 38899;
    char* udpAdd;

    struct {
        String On = "{\"id\":1,\"method\":\"setState\",\"params\":{\"state\":true}}";
        String Off = "{\"id\":1,\"method\":\"setState\",\"params\":{\"state\":false}}";
        String Dim = "{\"id\":1,\"method\":\"setState\",\"params\":{\"dimming\":";
        String Pilot = "{\"method\":\"getPilot\",\"params\":{}}";
        String UnDim = "{\"method\": \"setState\", \"params\":{\"dimming\":100}}";
    } Commands;

    void udpSend(String cmd);
    void checkPrintPacket();

public:
    WizLight(char* ipAddr);
    ~WizLight() = default;

    void On();
    void Off();
    void SetDim(unsigned char value);

    bool GetState();
};

#endif // !WIZLIGHT