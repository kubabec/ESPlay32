#ifndef MESSAGE_I2C_H
#define MESSAGE_I2C_H
#include "Arduino.h"
#include <vector>

enum MessageID : uint8_t
{
    REQUEST_ACTION = 74, /* Action on co-controler requested */
    ACTION_RESPONSE, /* Response to requested action */
    CONNECT_TO_NETWORK_SSID, /* Request WiFi connection to specified network */
    CONNECT_TO_NETWORK_PASSWORD, 
    GET_NETWORK_STATUS,
    CREATE_AP, /* Request access point creation */
    SLAVE_TO_MASTER_MSG, /* Information from co-controler to main device */
    UDP_OUTGOING_PACKAGE, /* Data requested to be sent via UDP */
    UDP_INCOMMING_PACKAGE, /* Data received from the network via UDP */
    WIFI_CONNECTION_LOST,
    SUBSYSTEM_STATUS,
    SUBSYSTEM_STATUS_SSID,
    SUBSYSTEM_STATUS_PASSWORD,
    SUBSYSTEM_NETWORK_DATA,
    NETWORK_DISCONNECT_REQUEST,
    INVALID, /* Wrong message content */
    UNKNOWN /* Uninitialized */
};

class MessageUART
{
    MessageID id = UNKNOWN; /* uint8_t */
    uint8_t totalSize = 0; /* Total size of message in bytes */
    std::vector<uint8_t> dataBuffer; /* Data buffer for message content */

    int byteIterationIndex = -1; /* current byte while iterating through all the message to send */
    
    static const uint8_t lastByteCheckValue = 0b10101010;
    void updateTotalSize();

    static bool validateMessageId(MessageID messageId);
    static bool validateTotalSize(uint8_t bufferSize, uint8_t secondByteValue);
    static bool validateLastByteValue(uint8_t lastByteValue);

public:
    MessageUART();
    MessageUART(MessageID myId);
    MessageUART(MessageID myId, byte* buffer, uint8_t bufferSize);

    MessageID getId();

    bool pushData(uint8_t data);
    bool pushData(uint8_t* arr, size_t size);
    bool pushData(std::string& data);

    size_t getSize();
    bool isValid();
    bool toByteArray(byte* bufferPtr, size_t sizeCheck);

    //static MessageUART fromByteArray(byte* dataPtr, uint8_t dataSize);
    static MessageUART fromUint8Vector(std::vector<uint8_t>& vec);
    static void serialPrintMessageUART(MessageUART& msg);

    /* Interfaces to reach byte by byte to transmitt via I2C*/
    /* Reset current intex counter */
    void resetByteIterationCount();
    /* Read current byte */
    uint8_t getCurrentByte();
    /* Moves to the next byte; if next byte exist returns true, otherwise false */
    bool switchToNextByte(); 



    // payload accessor
    std::vector<uint8_t>& getPayload();
};


#endif