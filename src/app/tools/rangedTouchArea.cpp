#include "app/tools/rangedTouchArea.hpp"

RangedTouchArea::RangedTouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah, int aMaxValue, std::function<void (int)> a_onTouchCallback)
    :x(ax), y(ay), w(aw), h(ah), maxValue(aMaxValue), onTouchCallback(a_onTouchCallback)
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
    if(onTouchCallback){
        onTouchCallback(value);
    }
}

bool RangedTouchArea::touchInput(int ax, int ay)
{
    if (ax >= x && ax <= (x + w) && ay >= y && ay <= (y + h)) {
        // Serial.println(String(ax));
        // Serial.println(String(x));
        // Serial.println(String(w));
        // Serial.println(String(maxValue));
        value = ((float)(ax - x) / (float)w) * (float)maxValue;
        // Serial.println(String(value));
        runCallback();
        return true;
    }
    return false;
}