#include "os/portableos.hpp"
#include "os/drivers/keyboarddriver.hpp"
#include "os/drivers/touchinputdriver.hpp"
#include "networkTools/uartCommunicator.hpp"
#include "networkTools/messageUDP.hpp"

#define MS_50 50
#define MS_200 200

void uartUdpRouterTask() 
{
    UARTCommunicator::task();
    DispatcherUART::task();
}

// Initial arduino function
void setup()
{
    // Start serial communication
    Serial.begin(115200);
    // Serial2.begin(115200, SERIAL_8N1, 13, 12);

    DispatcherUART::readIncommingMessagesBuffer = UARTCommunicator::getReceivedMessagesBufferReference;
    UARTCommunicator::init();

    // Initialize PortableOS
    PortableOS::init();

    // Initialize keyboardDriver
    KeyboardDriver::init();

    // Initialize touch input driver
    TouchInputDriver::init();
    

}

// Use serial read characters instead of hardware input
void inputCharProxy(char charInput) {
    // Forward Input to PortableOS
    switch (charInput)
    {
    case 'a':
        PortableOS::input(BUTTON_A);
        break;
    case 'b':
        PortableOS::input(BUTTON_B);
        break;
    case 'c':
        PortableOS::input(BUTTON_C);
        break;
    case 'd':
        PortableOS::input(BUTTON_D);
        break;
    case 'e':
        PortableOS::input(BUTTON_E);
        break;
    case 'f':
        PortableOS::input(BUTTON_F);
        break;
    case 'k':
        PortableOS::input(BUTTON_K);
        break;
    default:
        break;
    }
}

// Arduino main loop
void loop()
{
    // Process serial communication
    while (Serial.available()) {
        char readValue = Serial.read();
        inputCharProxy(readValue);
    }

    static unsigned long long timer10 = 0;
    static unsigned long long timer50 = 0;
    static unsigned long long timer1000 = 0;

    // Process keyboard
    KeyboardDriver::task();
    TouchInputDriver::task();
    uartUdpRouterTask();

    // Process 25ms timer event
    if (millis() - timer10 >= 10) {
        KeyboardDriver::processAnalog();
        PortableOS::osTask10ms();
        timer10 = millis();
    } 

    // Process 1000ms timer event
    if (millis() - timer1000 >= 1000) {
        PortableOS::osTask1s();
        timer1000 = millis();
    }
}