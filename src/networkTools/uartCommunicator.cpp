#include <networkTools/uartCommunicator.hpp>
#include <HardwareSerial.h>

std::vector<MessageUART> UARTCommunicator::receivedMessages;

void UARTCommunicator::init()
{
    Serial2.begin(115200, SERIAL_8N1, 13, 12);
   
}

void UARTCommunicator::task()
{
    std::vector<uint8_t> receiveByteVector;

    while(Serial2.available())
    {   
        receiveByteVector.push_back(Serial2.read());
    }

    if(receiveByteVector.size() > 0){
        Serial.println("Number of received bytes : " + String(receiveByteVector.size()));
        // Push received message to receive buffer
        MessageUART receivedMessage = MessageUART::fromUint8Vector(receiveByteVector);

        for(auto& oneByte : receiveByteVector)
        {
            Serial.print(String((uint8_t)oneByte) + " ");
            
        }
        Serial.println();

        if(receivedMessage.isValid()){
            receivedMessages.push_back(receivedMessage); 
            Serial.println("Received valid message");
        }
        else
        {
            Serial.println("Received INVALID message!");
        }

        // TEST --------------
        // if(receivedMessages.size() > 0)
        // {
        //     Serial.println("Receivedmessages size > 0 in UARTCommunicator::task");
        //     MessageUART::serialPrintMessageUART(receivedMessages.at(0));
        // }
        // TEST --------------
    }
}


void UARTCommunicator::transmit(MessageUART& message)
{
    /* Reset iteration counter to start transmitting from beginning of the message */
    message.resetByteIterationCount();

    /* Start iterating through all the message bytes */
    while(message.switchToNextByte()){
        /* Transmit each byte separately */
        Serial2.write(message.getCurrentByte());
    }

    /* Flush the message */
    Serial2.flush();

    // TEST --------------
    // std::vector<uint8_t> receiveByteVector;
    // while(Serial2.available())
    // {
    //     receiveByteVector.push_back(Serial2.read());
    // }

    // if(receiveByteVector.size() > 0){
    //     // Push received message to receive buffer
    //     MessageUART receivedMessage = MessageUART::fromUint8Vector(receiveByteVector);
    //     if(receivedMessage.isValid()){
    //         receivedMessages.push_back(receivedMessage); 
    //     }
    // }
    // if(receivedMessages.size() > 0)
    // {
    //     MessageUART::serialPrintMessageUART(receivedMessages.at(0));
    // }
    // TEST --------------
}


std::vector<MessageUART>& UARTCommunicator::getReceivedMessagesBufferReference()
{
    return receivedMessages;
}