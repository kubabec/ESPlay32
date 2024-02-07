#include <networkTools/dispatcherUART.hpp>
#include <os/portableos.hpp>

// #include "udpAdapter.hpp"

// std::function<void()> DispatcherUART::onRequestActionCallback = callbacks::onRequestActionCallback;
// std::function<void()> DispatcherUART::onActionResponseCallback = callbacks::onActionResponseCallback;
// std::function<void()> DispatcherUART::onConnectToNetworkCallback = callbacks::onConnectToNetworkCallback;
// std::function<void()> DispatcherUART::onCreateApCallback = callbacks::onCreateApCallback;
// std::function<void()> DispatcherUART::onSlaveToMasterMsgCallback = callbacks::onSlaveToMasterMsgCallback;


/* Callback executed when there is UDP message received by UDPAdapter to be forwarded via UART */
std::function<void(MessageUDP&)> DispatcherUART::onUdpIncommingPackageCallback = callbacks::onUdpIncommingPackageCallback;

// std::function<void()> DispatcherUART::onInvalidCallback = callbacks::onInvalidCallback;
// std::function<void()> DispatcherUART::onUnknownCallback = callbacks::onUnknownCallback;


std::function< std::vector<MessageUART>&()> DispatcherUART::readIncommingMessagesBuffer;

#ifdef IS_UART_ROUTING_SLAVE
void DispatcherUART::task()
{
    // Is receive buffer getter assigned?
    if(readIncommingMessagesBuffer){
        // Read receivedBuffer
        std::vector<MessageUART>& receivedMessagesRef = readIncommingMessagesBuffer();
        // Is any message inside ?
        if(receivedMessagesRef.size() > 0)
        {
            // Dispatch each message
            for(MessageUART& message : receivedMessagesRef){
                switch(message.getId())
                {
                    // case REQUEST_ACTION:
                    //     if(DispatcherUART::onRequestActionCallback != nullptr)
                    //     {
                    //         DispatcherUART::onRequestActionCallback();
                    //     }
                    // break;


                    // case ACTION_RESPONSE:
                    //     if(DispatcherUART::onActionResponseCallback != nullptr)
                    //     {
                    //         DispatcherUART::onActionResponseCallback();
                    //     }
                    // break;


                    // case CONNECT_TO_NETWORK:
                    //     if(DispatcherUART::onConnectToNetworkCallback != nullptr)
                    //     {
                    //         DispatcherUART::onConnectToNetworkCallback();
                    //     }
                    // break;


                    // case CREATE_AP:
                    //     if(DispatcherUART::onCreateApCallback != nullptr)
                    //     {
                    //         DispatcherUART::onCreateApCallback();
                    //     }
                    // break;


                    // case SLAVE_TO_MASTER_MSG:
                    //     if(DispatcherUART::onSlaveToMasterMsgCallback != nullptr)
                    //     {
                    //         DispatcherUART::onSlaveToMasterMsgCallback();
                    //     }
                    // break;


                    case UDP_OUTGOING_PACKAGE:
                        {
                            /* Extract UDP message from UART message payload */
                            MessageUDP receivedUDPMessage = extractMessageUDP(message);
                            if(receivedUDPMessage.isValid()){
                                /* Pass extracted UDP Message to associated callback */
                                UDPAdapter::send(receivedUDPMessage);
                            }else
                            {
                                Serial.println("Trying to send invalid UDP aborted...");
                            }
                        }
                    break;


                    case UDP_INCOMMING_PACKAGE:
                        if(DispatcherUART::onUdpIncommingPackageCallback != nullptr)
                        {
                            // SLAVE DEVICE DOES NOT SUPPORT INCOMMING MESSAGE HANDLING IN DISPATCHER TASK
                            // MessageUDP receivedUDPMessage;
                            // DispatcherUART::onUdpIncommingPackageCallback(receivedUDPMessage);
                        }
                    break;


                    // case INVALID:
                    //     if(DispatcherUART::onInvalidCallback != nullptr)
                    //     {
                    //         DispatcherUART::onInvalidCallback();
                    //     }
                    // break;


                    // case UNKNOWN:
                    //     if(DispatcherUART::onUnknownCallback != nullptr)
                    //     {
                    //         DispatcherUART::onUnknownCallback();
                    //     }
                    // break;


                    default : break;
                }

            }
        }
        // Cleas received messages vector as they are already dispatched to the system
        receivedMessagesRef.clear();
    }
}
#else 
void DispatcherUART::task()
{
    // Is receive buffer getter assigned?
    if(readIncommingMessagesBuffer){
        // Read receivedBuffer
        std::vector<MessageUART>& receivedMessagesRef = readIncommingMessagesBuffer();
        // Is any message inside ?


        // TEST --------------
        // if(receivedMessagesRef.size() > 0 ){
        //     Serial.println("Received buffer size: " + String(receivedMessagesRef.size()));
        //     MessageUART::serialPrintMessageUART(receivedMessagesRef.at(0));
        // }
        // TEST --------------

        if(receivedMessagesRef.size() > 0)
        {
            // Dispatch each message
            for(MessageUART& message : receivedMessagesRef){
                switch(message.getId())
                {
                    // case REQUEST_ACTION:
                    //     if(DispatcherUART::onRequestActionCallback != nullptr)
                    //     {
                    //         DispatcherUART::onRequestActionCallback();
                    //     }
                    // break;


                    // case ACTION_RESPONSE:
                    //     if(DispatcherUART::onActionResponseCallback != nullptr)
                    //     {
                    //         DispatcherUART::onActionResponseCallback();
                    //     }
                    // break;


                    // case CONNECT_TO_NETWORK:
                    //     if(DispatcherUART::onConnectToNetworkCallback != nullptr)
                    //     {
                    //         DispatcherUART::onConnectToNetworkCallback();
                    //     }
                    // break;


                    // case CREATE_AP:
                    //     if(DispatcherUART::onCreateApCallback != nullptr)
                    //     {
                    //         DispatcherUART::onCreateApCallback();
                    //     }
                    // break;


                    // case SLAVE_TO_MASTER_MSG:
                    //     if(DispatcherUART::onSlaveToMasterMsgCallback != nullptr)
                    //     {
                    //         DispatcherUART::onSlaveToMasterMsgCallback();
                    //     }
                    // break;


                    case UDP_OUTGOING_PACKAGE:
                        {
                            // NO OUTGOING PACKAGE CALLBACK ASSIGNED ON MASTER DEVICE

                            // /* Extract UDP message from UART message payload */
                            // MessageUDP receivedUDPMessage = extractMessageUDP(message);
                            // if(receivedUDPMessage.isValid()){
                            //     /* Pass extracted UDP Message to associated callback */
                            //     // UDPAdapter::send(receivedUDPMessage);
                            // }else
                            // {
                            //     Serial.println("Trying to send invalid UDP aborted...");
                            // }
                            // NO UDP SENDING ON MASTER DEVICE
                            //Serial.println("Trying to send UDP message on master device");
                        }
                    break;


                    case UDP_INCOMMING_PACKAGE:
                    {
                        MessageUDP receivedUDPMessage = extractMessageUDP(message);
                        PortableOS::udpMessageRecieved(receivedUDPMessage);
                    }
                    break;


                    // case INVALID:
                    //     if(DispatcherUART::onInvalidCallback != nullptr)
                    //     {
                    //         DispatcherUART::onInvalidCallback();
                    //     }
                    // break;


                    // case UNKNOWN:
                    //     if(DispatcherUART::onUnknownCallback != nullptr)
                    //     {
                    //         DispatcherUART::onUnknownCallback();
                    //     }
                    // break;


                    default : break;
                }

            }
        }
        // Cleas received messages vector as they are already dispatched to the system
        receivedMessagesRef.clear();
    }
}
#endif 

MessageUDP DispatcherUART::extractMessageUDP(MessageUART& uartMessage)
{
    std::vector<uint8_t>& udpMessageAsByteVecRef = uartMessage.getPayload();

    MessageUDP extractedMessage = MessageUDP::fromUint8Vector(udpMessageAsByteVecRef);
    if(extractedMessage.isValid()){
        return extractedMessage;
    }

    return MessageUDP{-1, MessageUDP::IPAddr{0,0,0,0}, -1};
}