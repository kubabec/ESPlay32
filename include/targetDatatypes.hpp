#ifndef TARGETDATATYPES_HPP
#define TARGETDATATYPES_HPP
#include "targetSelection.hpp"


#ifndef EMULATOR
    // Console code
    #include <FS.h>
    #include <TFT_eSPI.h>
    #include <SPI.h>
    #include <Arduino.h>
    #include <Vector.h>
#else
    // Emulator code
    #include <QString>
    #include <vector>
    #include <QColor>

    #define TFT_GREENYELLOW 0x99ff33
    #define TFT_BLUE 0x0000FF
    #define TFT_GREEN 0x00FF00
    #define TFT_YELLOW 0xffff00
    #define TFT_CYAN 0x00ffff
    #define TFT_BLACK 0x000000
    #define TFT_BROWN 0x996600
    #define TFT_WHITE 0xFFFFFF
    #define TFT_ORANGE 0xffcc00
    #define TFT_RED 0xff0000
    #define TFT_LIGHTGREY 0x669999


    using String = QString;
    template <class T>
    using Vector = std::vector<T>;

//    #ifndef serial_h
//    #define serial_h
//    class serial
//    {
//    public:
//        serial() = default;
//        void println() {
//            // do nothing
//        };
//    };

//    serial Serial;
//    #endif

//    #ifndef millis_h
//    #define millis_h
//    long long millis() {
//        // do nothing;
//        return 0;
//    }
//    #endif

#endif

#endif // TARGETDATATYPES_HPP
