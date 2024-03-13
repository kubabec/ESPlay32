#ifndef BOOL_BUTTON
#define BOOL_BUTTON

#include <app/tools/touchinputproxy.h>
#include <os/displayprovider.hpp>
#include <app/tools/character2d.hpp>

class BoolButton {
    bool isOn = false;
    uint16_t x = 0.f, y = 0.f;
    uint16_t w = 50, h = 25;
    TouchInputProxy hitbox;
    void switchButton();
    bool isEnablingAnimationStarted = false;
    bool isRenderNeeded = true;
    bool isRectangleDrawn = false;
    uint16_t disabledX, enabledX;

    Character2D buttonIcon{x, y, h};
    public:
    BoolButton(uint16_t ax, uint16_t ay);
    void draw(DisplayProvider& display);
    void touchInput(int x, int y);
    void update();
};

#endif