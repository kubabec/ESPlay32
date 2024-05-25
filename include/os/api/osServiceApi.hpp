#ifndef OS_SERVICE_API_H
#define OS_SERVICE_API_H
#include <functional>
#include "networkTools/messageUDP.hpp"
#include "os/osDatatypes.hpp"
#include "app/runtimeApplication.hpp"

class OS_SERVICE_API
{
    public:
    static const std::function<bool(RuntimeApplication* overtakerPtr)> contextOvertake;
    static const std::function<void(void)> contextRelease;
};


#endif