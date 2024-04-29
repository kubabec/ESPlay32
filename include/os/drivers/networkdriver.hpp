#ifndef NETWORK_DRIVER_H
#define NETWORK_DRIVER_H

#include "WiFi.h"
#include "WiFiUdp.h"


class NetworkDriver
{
    static WiFiServer server;
    
public:
    static void task();
    static void init();

};


#endif