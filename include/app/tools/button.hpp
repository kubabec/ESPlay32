#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "os/displayprovider.hpp"
#include "app/tools/touchinputproxy.h"
#include <functional>

class Button {
    public:
    uint16_t x, y, w, h;
    uint16_t buttonId;
    uint16_t color;
    int colors [2] {TFT_BLUE, TFT_RED};
    int indexColor = 0;
    bool pressed = false;
    bool needsRedraw = true;
    TouchInputProxy touchAreaBox;
    const char* label; 


    Button(uint16_t argx, uint16_t argy,uint16_t argw, uint16_t argh ,const char* arglabel);
       
    void drawButton(DisplayProvider &display);
    void touchArea(int tx, int ty);

};

#endif