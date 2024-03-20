#ifndef SLIDER
#define SLIDER

#include <app/tools/rangedTouchArea.hpp>
#include <os/displayprovider.hpp>
#include <app/tools/character2d.hpp>

class Slider {
    bool isOn = false;
    uint16_t x = 0.f, y = 0.f;
    uint16_t w = 150, h = 50;
    RangedTouchArea hitbox;
    void sliderValueChange(int value);
    bool isRenderNeeded = true;
    std::function<void (bool)> callbackOnStatusChange;

    Character2D buttonIcon{-100, -100, h / 2};
    public:
    Slider(uint16_t ax, uint16_t ay, std::function<void (bool)> callback);
    void draw(DisplayProvider& display);
    void touchInput(int x, int y);
    void update();
};

#endif