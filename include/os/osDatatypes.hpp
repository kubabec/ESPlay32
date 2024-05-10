#ifndef OS_DATATYPES_H
#define OS_DATATYPES_H
#include <Arduino.h>

typedef struct {
    bool isWiFiConnectedFlag;
    bool wasWiFiRequestedFlag;
    uint8_t ssidLength;
    uint8_t passwordLength;
    String lastConnectedSSID;
    String lastConnectedPassword;
    uint8_t ipOctet1;
    uint8_t ipOctet2;
    uint8_t ipOctet3;
    uint8_t ipOctet4;
}SubsystemStatusData;

typedef struct {
    bool isCommunicating = false;
    SubsystemStatusData data;
}SubsystemOverview;


#endif