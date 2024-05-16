#ifndef STRING_BUFER_H
#define STRING_BUFER_H

#include <Arduino.h>
#include <vector>
class StringBuffer
{
    #define STRING_BUFFER_SIZE 40
    public:
    char buffer[STRING_BUFFER_SIZE] = {'\0'};

    StringBuffer(const String& arduinoString){
        memset(buffer, '\0', STRING_BUFFER_SIZE);
        
        if(arduinoString.length() < STRING_BUFFER_SIZE){
            memcpy(buffer, arduinoString.c_str(), arduinoString.length());
        }
    }

    StringBuffer(char* memory)
    {
        memset(buffer, '\0', STRING_BUFFER_SIZE);
        memcpy(buffer, memory, STRING_BUFFER_SIZE);
    }

    StringBuffer(std::vector<uint8_t>& bytes)
    {
        memset(buffer, '\0', STRING_BUFFER_SIZE);
        if(bytes.size() == STRING_BUFFER_SIZE){
            memcpy(buffer, &bytes.at(0), STRING_BUFFER_SIZE);
        }
    }

    String toString()
    {
        String retVal(buffer);
        return retVal;
    };

    char* getBuffer()
    {
        return buffer;
    }

    uint8_t getSize()
    {
        return STRING_BUFFER_SIZE;
    }
};

#endif