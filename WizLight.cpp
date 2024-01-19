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

void WizLight::udpSend(String cmd) {
    byte buffer[cmd.length() + 1];
    cmd.getBytes(buffer, cmd.length() + 1);
    udp.beginPacket(udpAdd, udpPort);
    udp.write(buffer, cmd.length());
    udp.endPacket();
    getPacket();
}

char* WizLight::getPacket() {
    char packet[255];
    int packetSize = udp.parsePacket();
    if (packetSize) {
        int len = udp.read(packet, 255);
        if (len > 0) {
            packet[len] = '\0';
        }
    }
    return packet;
}

WizLightInfo WizLight::GetState() {
    StaticJsonDocument<250> doc;
    
    udpSend(Commands.Pilot);
    char* json = getPacket();

    DeserializationError error = deserializeJson(doc, json);

    if (error) {
        Serial.println("Error parsing Json");
        return currentState;
    }

    currentState.state = doc["results"][3];
    Serial.println(currentState.state);

    return this->currentState;
}