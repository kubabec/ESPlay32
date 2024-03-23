#ifndef SLIDER
#define SLIDER

#include <app/tools/rangedTouchArea.hpp>
#include <os/displayprovider.hpp>
#include <app/tools/character2d.hpp>

class Slider {
    bool isOn = false;
    int sliderID;
    uint16_t x = 0.f, y = 0.f;
    uint16_t w = 150, h = 30;
    RangedTouchArea hitbox;
    void sliderValueChange(int value);
    bool isRenderNeeded = true;
    std::function<void (int, int)> callbackOnStatusChange;

    Character2D buttonIcon{-100, -100, h / 2};
    public:
    Slider(uint16_t ax, uint16_t ay, int asliderID, std::function<void (int, int)> callback);
    void draw(DisplayProvider& display);
    void touchInput(int x, int y);
    void update();
};

#endif