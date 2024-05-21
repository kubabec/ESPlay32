#include "networkTools/dispatcherUART.hpp"
#include "os/portableos.hpp"


SubsystemStatusData extractSubsystemData(MessageUART& uartMessage);

// #include "udpAdapter.hpp"

// std::function<void()> DispatcherUART::onRequestActionCallback = callbacks::onRequestActionCallback;
// std::function<void()> DispatcherUART::onActionResponseCallback = callbacks::onActionResponseCallback;
// std::function<void()> DispatcherUART::onConnectToNetworkCallback = callbacks::onConnectToNetworkCallback;
// std::function<void()> DispatcherUART::onCreateApCallback = callbacks::onCreateApCallback;
// std::function<void()> DispatcherUART::onSlaveToMasterMsgCallback = callbacks::onSlaveToMasterMsgCallback;


/* Callback executed when there is UDP message received by UDPAdapter to be forwarded via UART */
//std::function<void(MessageUDP&)> DispatcherUART::onUdpIncommingPackageCallback = callbacks::onUdpIncommingPackageCallback;

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

                    case SUBSYSTEM_STATUS:
                    {
                        //Serial.print("|");
                        SubsystemStatusData receivedSubsystemData = extractSubsystemData(message);
                        PortableOS::subsystemStatusReceived(receivedSubsystemData);
                    }
                    break;

                    case SUBSYSTEM_STATUS_SSID:
                    {
                        String ssid(extractStringFromPayload(message).c_str());
                        PortableOS::networkSsidReceived(ssid);
                    }
                    break;

                    case SUBSYSTEM_STATUS_PASSWORD:
                    {
                        String password(extractStringFromPayload(message).c_str());
                        PortableOS::networkPasswordReceived(password);
                    }
                    break;

                    case SUBSYSTEM_NETWORK_DATA:
                    {
                        NetworkDataUARTMessage data =  extractNetworkDataFromPayload(message);
                        PortableOS::networkDataReceived(data);
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

SubsystemStatusData extractSubsystemData(MessageUART& uartMessage)
{
    std::vector<uint8_t>& subsystemDataAsByteVecRef = uartMessage.getPayload();
    uint16_t controlSize = 0;
    SubsystemStatusData receivedData;

    memcpy(&receivedData, &subsystemDataAsByteVecRef.at(0), sizeof(SubsystemStatusData));
    
//     memcpy(&receivedData.isWiFiConnectedFlag, &subsystemDataAsByteVecRef.at(0), sizeof(receivedData.isWiFiConnectedFlag));
//     uint16_t offset = 0 + sizeof(receivedData.isWiFiConnectedFlag);

//     memcpy(&receivedData.wasWiFiRequestedFlag, &subsystemDataAsByteVecRef.at(offset), sizeof(receivedData.wasWiFiRequestedFlag));
//     offset += sizeof(receivedData.wasWiFiRequestedFlag);


//     // Copy ssid string
//     // String ssid = String(&subsystemDataAsByteVecRef.at(offset), receivedData.ssidLength);
//     // offset += receivedData.ssidLength;

//     // String password = String(&subsystemDataAsByteVecRef.at(offset), receivedData.passwordLength);
//     // offset += receivedData.passwordLength;


//     memcpy(&receivedData.ipOctet1, &subsystemDataAsByteVecRef.at(offset), sizeof(receivedData.ipOctet1));
//     offset += sizeof(receivedData.ipOctet1);

//     memcpy(&receivedData.ipOctet2, &subsystemDataAsByteVecRef.at(offset), sizeof(receivedData.ipOctet2));
//     offset += sizeof(receivedData.ipOctet2);

//     memcpy(&receivedData.ipOctet3, &subsystemDataAsByteVecRef.at(offset), sizeof(receivedData.ipOctet3));
//     offset += sizeof(receivedData.ipOctet3);

//     memcpy(&receivedData.ipOctet4, &subsystemDataAsByteVecRef.at(offset), sizeof(receivedData.ipOctet4));

//     // receivedData.lastConnectedSSID = ssid;
//     // receivedData.lastConnectedPassword = password;
//    // memcpy(&receivedData.passwordLength, &subsystemDataAsByteVecRef.at(offset), sizeof(receivedData.passwordLength));



//     // if(subsystemDataAsByteVecRef.size() == sizeof(SubsystemStatusData))
//     // {
//     //     memcpy(&retVal, &subsystemDataAsByteVecRef.at(0), subsystemDataAsByteVecRef.size());
//     // }


    return receivedData;
}

std::string DispatcherUART::extractStringFromPayload(MessageUART& uartMessage) {
    std::string str;
    std::vector<uint8_t>& payloadRef = uartMessage.getPayload();
    for (auto& character : payloadRef) {
        str += (char)character;
    }
    return str;
}

NetworkDataUARTMessage DispatcherUART::extractNetworkDataFromPayload(MessageUART& uartMessage)
{
    NetworkDataUARTMessage retVal;
    if(uartMessage.getPayload().size() == (STRING_BUFFER_SIZE*2))
    {
        memcpy(&retVal, &uartMessage.getPayload().at(0), uartMessage.getPayload().size());
    }

    return retVal;
}