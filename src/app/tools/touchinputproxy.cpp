#include "app/tools/touchinputproxy.h"

TouchInputProxy::TouchInputProxy()
{

}

void TouchInputProxy::addTouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah, std::function<void ()> a_onTouchCallback)
{
    touchAreaContainer.push_back({ax, ay, aw, ah, a_onTouchCallback});
}

void TouchInputProxy::addTouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah, std::function<void (int)> a_onTouchCallback, int aidentifier)
{
    touchAreaContainer.push_back({ax, ay, aw, ah, a_onTouchCallback, aidentifier});
}

void TouchInputProxy::clearTouchAreas()
{
    touchAreaContainer.clear();
}

uint8_t TouchInputProxy::getTouchAreasCount()
{
    return touchAreaContainer.size();
}

void TouchInputProxy::touchInput(int x, int y)
{
    for (int i = touchAreaContainer.size() - 1; i > -1; i--) {
        if (touchAreaContainer.at(i).touchInput(x, y)) {
            break;
        }
    }
}
