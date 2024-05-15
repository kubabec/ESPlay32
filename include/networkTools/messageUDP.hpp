#ifndef MESSAGE_UDP_H
#define MESSAGE_UDP_H
#include "Arduino.h"
#include <vector>
// #include <WiFi.h>
// #include <WiFiUdp.h>

class MessageUDP
{
public:
    struct IPAddr{
        uint8_t element1;
        uint8_t element2;
        uint8_t element3;
        uint8_t element4;

        bool operator==(const IPAddr& rhv)
        {
            if(this->element1 == rhv.element1 &&
                this->element2 == rhv.element2 &&
                this->element3 == rhv.element3 &&
                this->element4 == rhv.element4)
                {
                    return true;
                }

            return false;
        }
    };

private:

    int id = -1; /* uint8_t */
    uint8_t totalSize = 0; /* Total size of message in bytes */
    IPAddr ipAddress{0, 0, 0, 0};
    int udpPort = 3333;

    std::vector<byte> dataBuffer; /* Data buffer for message content */

    int byteIterationIndex = -1; /* current byte while iterating through all the message to send */
    
    static const uint8_t lastByteCheckValue = 0b01010101;
    void updateTotalSize();

    static bool validateMessageId(int messageId);
    static bool validateTotalSize(uint8_t bufferSize, uint8_t secondByteValue);
    static bool validateLastByteValue(uint8_t lastByteValue);
    static bool validateIpAddress(IPAddr& addr);

    static uint8_t getMinimumSize();

public:

    MessageUDP();
    MessageUDP(int myId, MessageUDP::IPAddr addr, int port);
    MessageUDP(int myId, MessageUDP::IPAddr addr, int port, byte* buffer, uint8_t bufferSize);

    int getId();


    void setIpAddress(MessageUDP::IPAddr addr);
    void setPort(int port);

    bool pushData(byte data);
    bool pushData(byte* arr, size_t size);

    size_t getSize();
    bool isValid();
    bool toByteArray(byte* bufferPtr, size_t sizeCheck);

    //static MessageUART fromByteArray(byte* dataPtr, uint8_t dataSize);
    static MessageUDP fromUint8Vector(std::vector<uint8_t>& vec);
    static void serialPrintMessageUDP(MessageUDP& msg);

    /* Interfaces to reach byte by byte to transmitt via I2C*/
    /* Reset current intex counter */
    void resetByteIterationCount();
    /* Read current byte */
    uint8_t getCurrentByte();
    /* Moves to the next byte; if next byte exist returns true, otherwise false */
    bool switchToNextByte(); 

    // payload accessor
    std::vector<uint8_t>& getPayload();

    int getPort();
    MessageUDP::IPAddr getIPAddress();
};


#endif