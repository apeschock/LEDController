#include "WizLight.h"

WizLight::WizLight(char* ipAddr) {
    udpAdd = ipAddr;
    udp.begin(udpPort);
}

void WizLight::On() {
    udpSend(Commands.On);
}

void WizLight::Off() {
    udpSend(Commands.Off);
}

void WizLight::SetDim(unsigned char value) {
    String cmd = Commands.Dim;
    cmd = cmd + value + "}}";
    udpSend(cmd);
}

bool WizLight::GetState() {
    return false;
}

void WizLight::udpSend(String cmd) {
    byte buffer[cmd.length() + 1];
    cmd.getBytes(buffer, cmd.length() + 1);
    udp.beginPacket(udpAdd, udpPort);
    udp.write(buffer, cmd.length());
    udp.endPacket();
    checkPrintPacket();
}

void WizLight::checkPrintPacket() {
    char packet[255];
    int packetSize = udp.parsePacket();
    if (packetSize) {
        int len = udp.read(packet, 255);
        if (len > 0) {
            packet[len] = '\0';
        }
    }
}