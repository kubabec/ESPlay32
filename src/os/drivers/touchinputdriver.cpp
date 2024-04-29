#include "os/drivers/touchinputdriver.hpp"
#include "os/portableos.hpp"


// This is the file name used to store the touch coordinate
// calibration data. Change the name to start a new calibration.
#define CALIBRATION_FILE "/TouchCalData3"

// Set REPEAT_CAL to true instead of false to run calibration
// again, otherwise it will only be done once.
// Repeat calibration if you change the screen rotation.
#define REPEAT_CAL false

// Comment out to stop drawing black spots
#define BLACK_SPOT

#ifndef EMULATOR
TFT_eSPI* TouchInputDriver::ptr_tft = nullptr;
#endif
bool TouchInputDriver::touchEnabled = false;
uint16_t TouchInputDriver::calibrationData[5] = {233, 3657, 199, 3679, 7};

// void TouchInputDriver::force_calibration()
// {
// #ifndef EMULATOR
//     uint16_t calData[5];
//     // data not valid so recalibrate
//     ptr_tft->fillScreen(TFT_BLACK);
//     ptr_tft->setCursor(20, 0);
//     ptr_tft->setTextFont(2);
//     ptr_tft->setTextSize(1);
//     ptr_tft->setTextColor(TFT_WHITE, TFT_BLACK);

//     ptr_tft->println("Touch corners as indicated");

//     ptr_tft->setTextFont(1);
//     ptr_tft->println();

//     if (REPEAT_CAL) {
//       // tft.setTextColor(TFT_RED, TFT_BLACK);
//       // tft.println("Set REPEAT_CAL to false to stop this running again!");
//     }

//     ptr_tft->calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);
//     Serial.println(calData[0]);
//     Serial.println(calData[1]);
//     Serial.println(calData[2]);
//     Serial.println(calData[3]);
//     Serial.println(calData[4]);

//     ptr_tft->setTextColor(TFT_GREEN, TFT_BLACK);
//     ptr_tft->println("Calibration complete!");

//     // store data
//     // fs::File f =  SPIFFS.open(CALIBRATION_FILE, "w");
//     // if (f) {
//     //   f.write((const unsigned char *)calData, 14);
//     //   f.close();
//     // }
// #endif
// }

// void TouchInputDriver::touch_calibrate()
// {
// #ifndef EMULATOR
//   uint16_t calData[5];
//   uint8_t calDataOK = 0;

//   // check file system exists
//   // if (!SPIFFS.begin()) {
//   //   Serial.println("Formatting file system");
//   //   SPIFFS.format();
//   //   SPIFFS.begin();
//   // }

//   // check if calibration file exists and size is correct
//   // if (SPIFFS.exists(CALIBRATION_FILE)) {
//   //   if (REPEAT_CAL)
//   //   {
//   //     // Delete if we want to re-calibrate
//   //     SPIFFS.remove(CALIBRATION_FILE);
//   //   }
//   //   else
//   //   {
//   //       fs::File f =  SPIFFS.open(CALIBRATION_FILE, "r");
//   //       if (f) {
//   //           if (f.readBytes((char *)calData, 14) == 14)
//   //           calDataOK = 1;
//   //           f.close();
//   //       }
//   //   }
//   // }

//   if (calDataOK && !REPEAT_CAL) {
//     // calibration data valid
//     ptr_tft->setTouch(calData);
//   } else {
//     force_calibration();
//   }


//   ptr_tft->fillScreen(TFT_BLACK);

// #endif
// }

#ifndef EMULATOR
void TouchInputDriver::setTftAccess(TFT_eSPI* ptr)
{
    ptr_tft = ptr;
}
#endif

void TouchInputDriver::init()
{
#ifndef EMULATOR
    // call screen calibration if there is access to tft granted
    if(ptr_tft != nullptr){
       ptr_tft->setTouch(calibrationData);
    }
#else

#endif

}

void TouchInputDriver::calibrate()
{
#ifndef EMULATOR
    if(ptr_tft != nullptr){
        //force_calibration();
    }
#else

#endif
}

void TouchInputDriver::task()
{
#ifndef EMULATOR
    if(touchEnabled &&  ptr_tft != nullptr){
        uint16_t x, y;

        //See if there's any touch data for us
        if (ptr_tft->getTouch(&x, &y))
        {
            PortableOS::touchInput(x, y);
        }
    }
#else


#endif
}


void TouchInputDriver::enableTouch()
{
    touchEnabled = true;
}

void TouchInputDriver::disableTouch()
{
    touchEnabled = false;
}

bool TouchInputDriver::isTouchEnabled()
{
    return touchEnabled;
}
