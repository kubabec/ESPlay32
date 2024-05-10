#ifndef OS_API_H
#define OS_API_H
#include <functional>
#include "networkTools/messageUDP.hpp"
#include "os/osDatatypes.hpp"

class OS_API
{
    public:
    static const std::function<bool(MessageUDP& data)> sendUdpMessage;
    static const std::function<void(std::string ssid, std::string password)> connectToNetwork;
    static const std::function<const SubsystemOverview(void)> getSubsystemOverview;
};


#endif