#ifndef OS_DATATYPES_H
#define OS_DATATYPES_H
#include <Arduino.h>
#include "networkTools/stringBuffer.hpp"


typedef struct {
    String ssid;
    String password;
}NetworkCredentials;

typedef struct {
    String title;
    String text;
    uint16_t bgcolor;
}Notification;

#endif