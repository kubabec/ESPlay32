#include <app/osapi.hpp>
#include <os/portableos.hpp>


const std::function<bool(MessageUDP& data)> OS_API::sendUdpMessage =
    PortableOS::sendUDP;

const std::function<void(std::string ssid, std::string password)> OS_API::connectToNetwork =
    PortableOS::connectToNetwork;