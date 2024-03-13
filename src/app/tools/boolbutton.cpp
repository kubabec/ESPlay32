#include <app/tools/boolbutton.hpp>


BoolButton::BoolButton(uint16_t ax, uint16_t ay) : x(ax), y(ay) {
    hitbox.addTouchArea(x, y, w, h,
    std::bind(&BoolButton::switchButton, this));
}

void BoolButton::switchButton() {
    isOn = !isOn;
}

void BoolButton::draw(DisplayProvider &display) {
    display.fillRect(x, y, w, h, TFT_WHITE);
    if(isOn) {
        display.fillCircle((int32_t)(x + (w / 4)),(int32_t)(y + (h / 2)), (int32_t)(w / 2), TFT_BLACK);
    }
    else {
        display.fillCircle(x + (w / 2 + w / 4), y + (h / 2), (int32_t)(w / 2), TFT_BLACK);
    }
    
}

void BoolButton::touchInput(int x, int y) {
    hitbox.touchInput(x, y);
}