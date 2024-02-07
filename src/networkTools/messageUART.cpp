#include <networkTools/messageUART.hpp>

String MessageIDtoString(MessageID& id)
{
    String text = "Invalid";
    switch(id)
    {
        case REQUEST_ACTION:
            text = "Request Action";
        break;
        case ACTION_RESPONSE:
            text = "Action Response";
        break;
        case SLAVE_TO_MASTER_MSG:
            text = "Slave to Master Message";
        break;
        case UDP_OUTGOING_PACKAGE:
            text = "UDP Outgoing Package";
        break;
        case UDP_INCOMMING_PACKAGE:
            text = "UDP Incomming Package";
        break;
        case INVALID:
            text = "Invalid";
        break;
        case UNKNOWN:
            text = "Unknown";
        break;

        default:
        break;
    }

    return text;
}


MessageUART::MessageUART()
{
    /* Initialize as empty message with unknown type */
    id = UNKNOWN;

    updateTotalSize();
}

MessageUART::MessageUART(MessageID myId)
{
    /* Initialize message with requested ID*/
    id = myId;

    updateTotalSize();
}

MessageUART::MessageUART(MessageID myId, byte* buffer, uint8_t bufferSize)
{
    /* Initialize message with requested ID*/
    id = myId;

    /* Copy received data to the buffer */
    if(buffer != nullptr && bufferSize > 0){
        for(int i = 0 ; i < bufferSize; i++)
        {
            dataBuffer.push_back(buffer[i]);
        }
    }
    updateTotalSize();
}

MessageID MessageUART::getId()
{
    return id;
}

bool MessageUART::pushData(uint8_t data){
    // Serial.println("Pushing " + String(int(data)));
    /* push single byte */
    dataBuffer.reserve(dataBuffer.size() + 1);
    // Serial.println("Resized buffer to " + String(dataBuffer.size()));
    dataBuffer.push_back(data);

    // Serial.println("Data pushed, updating message size ...");
    /* update total size */
    updateTotalSize();

    return true;
}

bool MessageUART::pushData(uint8_t* arr, size_t size)
{
    if(arr != nullptr)
    {
        /* Go through passed buffer */
        for(int i = 0; i < size; ++i)
        {
            /* Push each byte to the buffer */
            dataBuffer.push_back(arr[i]);
        }

        /* Update total size */
        updateTotalSize();
    }
    else{
        Serial.println("Nullptr passed to pushData");
    }

    return true;
}

size_t MessageUART::getSize()
{
    return totalSize;
}

bool MessageUART::toByteArray(byte* bufferPtr, size_t sizeCheck)
{
    if(sizeCheck == totalSize && bufferPtr != nullptr) /* check if received bufferPtr size is expected */
    {
        bufferPtr[0] = (byte)id; /* Message identifier as a first byte */
        bufferPtr[1] = (byte)totalSize; /* size checksum as a second byte */

        if(dataBuffer.size() > 0){ /* There are any data in the buffer */
            /* 2 - const number of bytes before carried data buffer */
            for(int i = 2 ; i < sizeCheck-1; i++) /* start copying from third byte */
            {
                bufferPtr[i]  = dataBuffer.at(i-2); /* copy all buffer data */
            }
        }
        bufferPtr[sizeCheck-1] = (byte)lastByteCheckValue; /* End of message byte */

        return true;
    }

    return false;
}

// MessageUART MessageUART::fromByteArray(byte* dataPtr, uint8_t dataSize)
// {
//     MessageUART returnedMessage(INVALID);

//     if(dataSize > 0){
//         MessageID tmpId = (MessageID)dataPtr[0];
//         uint8_t tmpSize = (uint8_t)dataPtr[1];
//         uint8_t tmpLastByte = (uint8_t)dataPtr[dataSize-1];
//         if( validateMessageId(tmpId) && 
//             validateTotalSize(dataSize, tmpSize) && 
//             validateLastByteValue(tmpLastByte) )
//         {
//             returnedMessage.id = tmpId;
//             returnedMessage.totalSize = tmpSize;
            
//             uint8_t dataOnlySize = tmpSize - 3 * sizeof(uint8_t);

//             returnedMessage.dataBuffer.reserve(dataOnlySize);

//             for(uint8_t i = 2; i < dataSize - 1; i ++)
//             {
//                 returnedMessage.dataBuffer.push_back(dataPtr[i]);
//             }
//         }
//     }

//     return returnedMessage;
// }

MessageUART MessageUART::fromUint8Vector(std::vector<uint8_t>& vec)
{
    // Serial.println("Constructing new message ...");
    MessageUART returnedMessage(INVALID);
    /* Minimum size is fulfilled */
    if(vec.size() >= 3){
        // Serial.println("Size correct.");
        MessageID tmpId = (MessageID)vec.at(0);
        uint8_t tmpSize = (uint8_t)vec.at(1);
        uint8_t tmpLastByte = (uint8_t)vec.at(vec.size()-1);
        // Serial.println("tmplastByte " + String(tmpLastByte));

        if( validateMessageId(tmpId) && 
            validateTotalSize(vec.size(), tmpSize) && 
            validateLastByteValue(tmpLastByte) )
        {
            // Serial.println("Validation completed successfully");
            returnedMessage.id = tmpId;
            returnedMessage.totalSize = tmpSize;
            
            uint8_t dataOnlySize = tmpSize - 3 * sizeof(uint8_t);

            if(dataOnlySize > 0){
                returnedMessage.dataBuffer.reserve(dataOnlySize);

                for(uint8_t i = 2; i < vec.size() - 1; i ++)
                {
                    returnedMessage.dataBuffer.push_back(vec.at(i));
                }
                // Serial.println("Data copying completed with payload size " + String(returnedMessage.dataBuffer.size()) + " bytes");
            }
        }
    }

    // Serial.println("Constructing new message done");
    return returnedMessage;
}


void MessageUART::updateTotalSize()
{
    /* MessageId + totalSizeChecksum + buffer size */
    totalSize = sizeof(uint8_t) + sizeof(uint8_t) + (dataBuffer.size() * sizeof(uint8_t)) + sizeof(uint8_t);

    // Serial.println("Size updated to " + String((int)totalSize)); 
}

bool MessageUART::validateMessageId(MessageID messageId)
{
    bool retVal = false;
    for(uint8_t i = (uint8_t)REQUEST_ACTION; i <= (uint8_t)UNKNOWN; i++)
    {
        if(messageId == i)
        {
            retVal = true;
            // Serial.println("Message ID validation correct");
            break;
        }
    }

    // if(retVal == false){
    //     Serial.println("Message ID validation INCORRECT");
    // }
    return retVal;
}

bool MessageUART::validateTotalSize(uint8_t bufferSize, uint8_t secondByteValue)
{
    if(bufferSize == secondByteValue)
    {
        // Serial.println("Total size validation correct");
        return true;
    }
    // Serial.println("Total size validation INCORRECT");
    return false;
}

bool MessageUART::validateLastByteValue(uint8_t lastByteValue)
{
    // Serial.println("lastByteValue : " + String(lastByteValue));
    if(lastByteValue == lastByteCheckValue)
    {
        // Serial.println("Checksum validation correct");
        return true;
    }
    // Serial.println("Checksum validation INCORRECT");
    return false;
}

bool MessageUART::isValid()
{
    return (id != INVALID);
}

void MessageUART::resetByteIterationCount()
{
    byteIterationIndex = -1;
}

uint8_t MessageUART::getCurrentByte()
{
    // Serial.println("Total size: " + String(totalSize));
    // Serial.println("byteIterationIndex = " + String(byteIterationIndex));
    if(byteIterationIndex > 1)
    {
        if(byteIterationIndex != totalSize - 1)
        {
            // Serial.println("Returning payload byte at index: " + String(byteIterationIndex-2));
            return dataBuffer.at(byteIterationIndex-2); /* Return payload byte */
        }else
        {
            // Serial.println("Returning checkusm byte");
            return lastByteCheckValue;
        }
        
    }else {
        /* Return message ID*/
        if(byteIterationIndex == 0)
        {
            // Serial.println("Returning message ID");
            return (uint8_t)id;
            
        } else if (byteIterationIndex == 1) /* Return message size */
        {
            // Serial.println("Returning total size");
            return (uint8_t)totalSize;
        }
    }

    return -7;
}

bool MessageUART::switchToNextByte()
{
    // Increment index
    byteIterationIndex ++;

    // If next byte exists
    if(byteIterationIndex < (totalSize))
    {
        return true;
    }

    byteIterationIndex = -1;
    // No more bytes
    return false;
}


void MessageUART::serialPrintMessageUART(MessageUART& msg)
{
    Serial.println("$$ - - UART Message - - $$");

    Serial.println("ID : " + MessageIDtoString(msg.id));
    Serial.println("TotalSize : " + String(msg.totalSize));

    for(int i = 0 ; i < msg.dataBuffer.size(); i ++)
    {
        Serial.print((uint8_t)msg.dataBuffer.at(i));
        Serial.print(" ");
    }

    Serial.flush();
    Serial.println();
}


std::vector<uint8_t>& MessageUART::getPayload()
{
    return dataBuffer;
}
