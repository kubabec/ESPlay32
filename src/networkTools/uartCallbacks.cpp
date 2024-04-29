#include "networkTools/uartCallbacks.hpp"
#include "Arduino.h"

namespace callbacks{

// void onRequestActionCallback()
// {
//     Serial.println("onRequestActionCallback");
// }

// void onActionResponseCallback()
// {
//     Serial.println("onActionResponseCallback");
// }

// void onConnectToNetworkCallback()
// {
//     Serial.println("onConnectToNetworkCallback");
// }

// void onCreateApCallback()
// {
//     Serial.println("onCreateApCallback");
// }

// void onSlaveToMasterMsgCallback()
// {
//     Serial.println("onSlaveToMasterMsgCallback");
// }

// void onUdpOutgoingPackageCallback(MessageUDP& msg)
// {

// }

void onUdpIncommingPackageCallback(MessageUDP& msg)
{
    static int receivedCount = 0;

    receivedCount ++;
    Serial.println("onUdpIncommingPackageCallback");
    MessageUDP::serialPrintMessageUDP(msg);

    Serial.println();
    Serial.println("ReceivedCount:  " + String(receivedCount));
}

// void onInvalidCallback()
// {
//     Serial.println("onInvalidCallback");
// }

// void onUnknownCallback()
// {
//     Serial.println("onUnknownCallback");
// }

}
