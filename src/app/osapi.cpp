#include <app/osapi.hpp>
#include <os/portableos.hpp>


const std::function<bool(MessageUDP& data)> OS_API::sendUdpMessage =
    PortableOS::sendUDP;