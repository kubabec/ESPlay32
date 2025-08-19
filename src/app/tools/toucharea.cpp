#include "app/tools/toucharea.h"

TouchArea::TouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah, std::function<void ()> a_onTouchCallback)
    :x(ax), y(ay), w(aw), h(ah), onTouchCallback(a_onTouchCallback)
{

}

TouchArea::TouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah, std::function<void (int)> a_onTouchCallback, int aidentifier)
:x(ax), y(ay), w(aw), h(ah), onTouchCommonCallback(a_onTouchCallback), identifier(aidentifier)
{

}

TouchArea::TouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah)
:x(ax), y(ay), w(aw), h(ah)
{

}

uint16_t TouchArea::getX()
{
    return x;
}

uint16_t TouchArea::getY()
{
    return y;
}

uint16_t TouchArea::getWidth()
{
    return w;
}

uint16_t TouchArea::getHeight()
{
    return h;
}

void TouchArea::runCallback()
{
    if(identifier != -1) {
        onTouchCommonCallback(identifier);
    }
    else {
        onTouchCallback();
    }
}

bool TouchArea::touchInput(int ax, int ay)
{
    if (ax >= x && ax <= (x + w) && ay >= y && ay <= (y + h)) {
        runCallback();
        return true;
    }
    return false;
}
