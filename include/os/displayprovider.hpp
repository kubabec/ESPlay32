#ifndef DISPLAYPROVIDER_H
#define DISPLAYPROVIDER_H
#include "targetDatatypes.hpp"


#ifndef EMULATOR
    // Console code

    struct AppDisplayArea {
        uint16_t x;
        uint16_t y;
        uint16_t w;
        uint16_t h;
    };

    class DisplayProvider
    {
        // TFT display instance
        TFT_eSPI tftDisplay;
        AppDisplayArea currentAppDisplayArea {0, 0, 480, 320};
        bool isOverlayMode = false;

        public:
        DisplayProvider();

        void setTextSize(uint8_t s);
        void setTextFont(uint8_t f);
        void setTextColor(int c, int b);
        void setTextColor(int c);
        void fillScreen(uint32_t color);
        int16_t drawString(const String& string, int32_t poX, int32_t poY);
        void drawLine(int32_t xs, int32_t ys, int32_t xe, int32_t ye, uint32_t color);
        void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);
        void fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color);
        void loadFont(const uint8_t array[]);

        void setAppDisplayArea(AppDisplayArea displayArea);
        void setOverlayMode(bool isOverlay);

#ifndef EMULATOR
        TFT_eSPI* tftDirectAccess();
#endif


    };
#else
    // Emulator code
    #include <stdint.h>
    #include <QPixmap>
    #include <QPainter>
    #include <QPainterPath>

    struct AppDisplayArea {
        uint16_t x;
        uint16_t y;
        uint16_t w;
        uint16_t h;
    };

    class DisplayProvider
    {
        QPixmap* sceneData = nullptr;
        uint8_t fontSize = 6;
        uint8_t fontStyle = 1;
        int color = 0xffFF00;
        int colorBg = 0x000000;
        AppDisplayArea currentAppDisplayArea {0, 0, 480, 320};
        bool isOverlayMode = false;

        public:
        DisplayProvider();
        QPixmap *getSceneDataPtr();
        void generateScene();

        void setTextSize(uint8_t s);
        void setTextFont(uint8_t f);
        void setTextColor(int c, int b);
        void setTextColor(int c);
        void fillScreen(uint32_t color);
        int16_t drawString(const String& string, int32_t poX, int32_t poY);
        void drawLine(int32_t xs, int32_t ys, int32_t xe, int32_t ye, uint32_t color);
        void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);
        void fillCircle(int32_t x, int32_t y, int32_t r, uint32_t color);

        void setAppDisplayArea(AppDisplayArea displayArea);
        void setOverlayMode(bool isOverlay);


};
#endif
#endif
