#include "app/osapi.hpp"
#include "os/portableos.hpp"


const std::function<bool(MessageUDP& data)> OS_API::sendUdpMessage =
    PortableOS::sendUDP;


const std::function<bool(MessageUDP& data)> OS_API::sendUdpBroadcastMessage =
    PortableOS::sendBroadcast;

const std::function<void(std::string ssid, std::string password)> OS_API::connectToNetwork =
    PortableOS::connectToNetwork;

const std::function<const SubsystemOverview(void)> OS_API::getSubsystemOverview =
    PortableOS::getSubsystemOverview;

const std::function<void(void)> OS_API::disconnectWiFiNetwork =
    PortableOS::disconnectWiFiNetwork;

const std::function<void(Notification&)> pushNotification =
    PortableOS::pushNotification;