#ifndef BOOL_BUTTON
#define BOOL_BUTTON

#include <app/tools/touchinputproxy.h>
#include <os/displayprovider.hpp>
#include <app/tools/character2d.hpp>

class BoolButton {
    bool isOn = false;
    uint16_t x = 0.f, y = 0.f;
    uint16_t w = 50, h = 25;
    uint16_t id = -1;
    TouchInputProxy hitbox;
    void switchButton();
    bool isEnablingAnimationStarted = false;
    bool isDisablingAnimationStarted = false;
    bool isRenderNeeded = true;
    bool isRectangleDrawn = false;
    uint16_t disabledX, enabledX;
    std::function<void (int, bool)> callbackOnStatusChange;

    Character2D buttonIcon{-100, -100, h / 2};
    public:
    BoolButton(uint16_t ax, uint16_t ay, uint16_t aid, std::function<void (int, bool)> callback);
    void draw(DisplayProvider& display);
    void touchInput(int x, int y);
    void update();
    uint16_t getId();
};

#endif