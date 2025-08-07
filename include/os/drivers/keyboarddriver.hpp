#ifndef KEYBOARDDRIVER_H
#define KEYBOARDDRIVER_H
#include "os/portableos.hpp"
#include "Arduino.h"

// Select device
#define USING_ESP32

#ifdef USING_ESP32
    #define KEY_C_PIN 34
    #define KEY_A_PIN 35
    #define KEY_F_PIN 32
    #define KEY_K_PIN 33
    #define KEY_B_PIN 25
    #define KEY_D_PIN 26

    #define ANALOG_X_PIN 27
    #define ANALOG_Y_PIN 14
#else
    #define KEY_C_PIN PIN_D0
    #define KEY_A_PIN PIN_D1
    #define KEY_F_PIN PIN_D2
    #define KEY_K_PIN PIN_D6
    #define KEY_B_PIN PIN_D9
    #define KEY_D_PIN PIN_D11
#endif

#define NUMBER_OF_BUTTONS 6

#define BUTTON_REACTIVATION_TIME_MS 20
#define BUTTON_LONG_PRESS_CYCLE_TIMES 1500

typedef struct
{
    InputType btnType;
    int btnPin;
    bool isPressable = true;
    char btnName = '-';
    long btnPressedTime = 0;
    uint8_t longPressCounter = 0;
    bool isLongPress = false;
}HwButton;

class KeyboardDriver
{
    static HwButton buttons[NUMBER_OF_BUTTONS];
    
    
public:
    static void task();
    static void init();
    static void processAnalog();
};

#endif