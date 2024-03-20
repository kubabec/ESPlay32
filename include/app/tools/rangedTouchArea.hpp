#ifndef RANGEDTOUCHAREA_H
#define RANGEDTOUCHAREA_H

#include "targetDatatypes.hpp"
#include <functional>

class RangedTouchArea
{
    int identifier = -1;
    int value = 0;
    int maxValue = 0;
    uint16_t x, y, w, h;
    std::function<void (int)> onTouchCallback;
    std::function<void (int, int)> onTouchCommonCallback;
public:
    RangedTouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah, int aMaxValue, std::function<void (int)> a_onTouchCallback);
    RangedTouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah, int aMaxValue, std::function<void (int, int)> a_onTouchCallback, int aidentifier);
    uint16_t getX();
    uint16_t getY();
    uint16_t getWidth();
    uint16_t getHeight();
    void runCallback();
    bool touchInput(int ax, int ay);
};

#endif // RANGEDTOUCHAREA_H