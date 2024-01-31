#ifndef TOUCH_INPUT_DRIVER_H
#define TOUCH_INPUT_DRIVER_H

#include "targetDatatypes.hpp"
// #include "FS.h"



class TouchInputDriver {

    // static void touch_calibrate();
    // static void force_calibration();
    static uint16_t calibrationData[5];

#ifndef EMULATOR
    static TFT_eSPI* ptr_tft;
#endif

    static bool touchEnabled;

public:
    static void task();
    static void init();
    static void enableTouch();
    static void disableTouch();
    static bool isTouchEnabled();
    static void calibrate();

    #ifndef EMULATOR
    static void setTftAccess(TFT_eSPI* ptr);
    #endif

};

#endif
