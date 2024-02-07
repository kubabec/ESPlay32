#ifndef UARTCALLBACKS_H
#define UARTCALLBACKS_H

#include "messageUDP.hpp"



namespace callbacks {
// void onRequestActionCallback();
// void onActionResponseCallback();
// void onConnectToNetworkCallback();
// void onCreateApCallback();
// void onSlaveToMasterMsgCallback();
//void onUdpOutgoingPackageCallback(MessageUDP& msg);
void onUdpIncommingPackageCallback(MessageUDP& msg);
// void onInvalidCallback();
// void onUnknownCallback();

}

#endif