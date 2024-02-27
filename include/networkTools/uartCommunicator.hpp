#ifndef UARTCOMMUNICATOR_H
#define UARTCOMMUNICATOR_H

#include "messageUART.hpp"
#include "dispatcherUART.hpp"

class UARTCommunicator
{

    static std::vector<MessageUART> receivedMessages;

public:
    static void init();
    static void task();

    static void transmit(MessageUART& message);


    static std::vector<MessageUART>& getReceivedMessagesBufferReference();
};

#endif

