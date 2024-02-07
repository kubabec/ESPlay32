#ifndef DISPATCHER_I2C_H
#define DISPATCHER_I2C_H
#include "messageUART.hpp"
#include "messageUDP.hpp"
#include "uartCallbacks.hpp"
#include <functional>
#include <queue>

class DispatcherUART {
        static MessageUDP extractMessageUDP(MessageUART& uartMessage);

    public:
        // static std::function<void()> onRequestActionCallback;
        // static std::function<void()> onActionResponseCallback;
        // static std::function<void()> onConnectToNetworkCallback;
        // static std::function<void()> onCreateApCallback;
        // static std::function<void()> onSlaveToMasterMsgCallback;
        //static std::function<void(MessageUDP&)> onUdpOutgoingPackageCallback;
        static std::function<void(MessageUDP&)> onUdpIncommingPackageCallback;
        // static std::function<void()> onInvalidCallback;
        // static std::function<void()> onUnknownCallback;


        static std::function< std::vector<MessageUART>&()> readIncommingMessagesBuffer;

       // DispatcherUART() = default;

        static void task();

};


#endif