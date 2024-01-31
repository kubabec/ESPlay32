#ifndef TOUCHAREA_H
#define TOUCHAREA_H

#include "targetDatatypes.hpp"
#include <functional>

class TouchArea
{
    int identifier = -1;
    uint16_t x, y, w, h;
    std::function<void ()> onTouchCallback;
    std::function<void (int)> onTouchCommonCallback;
public:
    TouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah, std::function<void ()> a_onTouchCallback);
    TouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah, std::function<void (int)> a_onTouchCallback, int aidentifier);
    uint16_t getX();
    uint16_t getY();
    uint16_t getWidth();
    uint16_t getHeight();
    void runCallback();
    bool touchInput(int ax, int ay);
};

#endif // TOUCHAREA_H
