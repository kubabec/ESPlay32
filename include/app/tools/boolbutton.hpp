#ifndef BOOL_BUTTON
#define BOOL_BUTTON

#include <app/tools/touchinputproxy.h>
#include <os/displayprovider.hpp>

class BoolButton {
    bool isOn = false;
    uint16_t x = 0.f, y = 0.f;
    uint16_t w = 50, h = 25;
    TouchInputProxy hitbox;
    void switchButton();
    public:
    BoolButton(uint16_t ax, uint16_t ay);
    void draw(DisplayProvider& display);
    void touchInput(int x, int y);
};

#endif