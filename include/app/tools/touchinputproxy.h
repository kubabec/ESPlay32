#ifndef TOUCHINPUTPROXY_H
#define TOUCHINPUTPROXY_H

#include <vector>
#include "toucharea.h"

class TouchInputProxy
{
    std::vector<TouchArea> touchAreaContainer;
public:
    TouchInputProxy();
    void addTouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah, std::function<void ()> a_onTouchCallback);
    void addTouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah, std::function<void (int)> a_onTouchCallback, int aidentifier);
    void addTouchArea(uint16_t ax, uint16_t ay, uint16_t aw, uint16_t ah);
    void clearTouchAreas();
    uint8_t getTouchAreasCount();

    void touchInput(int x, int y);
};

#endif // TOUCHINPUTPROXY_H
