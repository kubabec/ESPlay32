#ifndef OS_DATATYPES_H
#define OS_DATATYPES_H
#include <Arduino.h>
#include "networkTools/stringBuffer.hpp"

typedef struct {
    bool isWiFiConnectedFlag;
    bool wasWiFiRequestedFlag;
    uint8_t ipOctet1;
    uint8_t ipOctet2;
    uint8_t ipOctet3;
    uint8_t ipOctet4;
}SubsystemStatusData;

typedef struct {
    String ssid;
    String password;
}NetworkCredentials;

typedef struct
{
    char ssid[STRING_BUFFER_SIZE];
    char password[STRING_BUFFER_SIZE];
}NetworkDataUARTMessage;


typedef struct {
    bool isCommunicating = false;
    SubsystemStatusData data;
    NetworkCredentials credentials;
}SubsystemOverview;

typedef struct {
    String title;
    String text;
    uint16_t bgcolor;
}Notification;

#endif