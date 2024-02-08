#ifndef OS_API_H
#define OS_API_H
#include <functional>
#include <networkTools/messageUDP.hpp>

class OS_API
{
    public:
    static const std::function<bool(MessageUDP& data)> sendUdpMessage;

};


#endif