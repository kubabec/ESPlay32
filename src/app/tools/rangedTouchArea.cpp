#include <app/tools/rangedTouchArea.hpp>

RangedTouchArea::RangedTouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah, int aMaxValue, std::function<void (int)> a_onTouchCallback)
    :x(ax), y(ay), w(aw), h(ah), maxValue(aMaxValue), onTouchCallback(a_onTouchCallback)
{

}

RangedTouchArea::RangedTouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah, int aMaxValue, std::function<void (int, int)> a_onTouchCallback, int aidentifier)
:x(ax), y(ay), w(aw), h(ah), maxValue(aMaxValue), onTouchCommonCallback(a_onTouchCallback), identifier(aidentifier)
{

}

uint16_t RangedTouchArea::getX()
{
    return x;
}

uint16_t RangedTouchArea::getY()
{
    return y;
}

uint16_t RangedTouchArea::getWidth()
{
    return w;
}

uint16_t RangedTouchArea::getHeight()
{
    return h;
}

void RangedTouchArea::runCallback()
{
    if(identifier != -1) {
        onTouchCommonCallback(identifier, value);
    }
    else {
        onTouchCallback(value);
    }
}

bool RangedTouchArea::touchInput(int ax, int ay)
{
    if (ax >= x && ax <= (x + w) && ay >= y && ay <= (y + h)) {
        value = (ax - x) / w * maxValue;
        runCallback();
        return true;
    }
    return false;
}