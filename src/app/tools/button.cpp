#include "app/tools/button.hpp"

Button::Button(uint16_t argx, uint16_t argy, uint16_t argw, uint16_t argh, const char* arglabel)
    : x(argx), y(argy), w(argw), h(argh), label(arglabel), color(TFT_BLUE), pressed(false) {}

void Button::drawButton(DisplayProvider &display) {
    if(needsRedraw) {
    display.fillRect(x, y, w, h, color);
    display.setTextColor(TFT_WHITE, TFT_WHITE);
    display.setTextSize(2);
    display.setTextFont(1);
    display.drawString(label, x + 5, y + h / 2 - 8);
    needsRedraw = false;
    }
}

void Button::touchArea(int tx, int ty) {
    // Check if the touch point is inside the button
    if (tx >= x && tx <= x + w && ty >= y && ty <= y + h) {
        needsRedraw = true; 
        if (pressed) {
        pressed = false;
        color = TFT_BLUE;
        } 
        else {
        pressed = true;
        color = TFT_RED;
        }
    }
}