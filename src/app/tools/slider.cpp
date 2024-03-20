#include <app/tools/slider.hpp>



Slider::Slider(uint16_t ax, uint16_t ay, std::function<void (bool)> acallback) : x(ax), y(ay),
 callbackOnStatusChange(acallback), hitbox(x, y, w, h, 255, std::bind(&Slider::sliderValueChange, this, std::placeholders::_1))
{
    buttonIcon.setColor(TFT_RED);
    buttonIcon.move(ax, (y + (h / 2)));
    buttonIcon.setLastXandY(buttonIcon.getX(), buttonIcon.getY());
    buttonIcon.setBgColor(TFT_WHITE);
}

void Slider::sliderValueChange(int value) { 
    float newX; 
    callbackOnStatusChange(value);
    newX = value * w / 255;
    newX += x;
    Serial.println("new value: " + (String(newX)));
    buttonIcon.setLastXandY(buttonIcon.getX(), buttonIcon.getY());
    buttonIcon.move(newX, buttonIcon.getY());
    isRenderNeeded = true;
}

void Slider::draw(DisplayProvider &display) {
    if (isRenderNeeded) {
        display.fillRect(x, y + 10, w, h - 20, TFT_WHITE);
        buttonIcon.draw(display);
       
    // if(isOn) {
    //     display.fillCircle((int32_t)(x + (w / 4)),(int32_t)(y + (h / 2)), (int32_t)(w / 4), TFT_BLACK);
    // }
    // else {
    //     display.fillCircle(x + (w / 2 + w / 4), y + (h / 2), (int32_t)(w / 4), TFT_BLACK);
    // }
        isRenderNeeded = false;
    }
    
    
}

void Slider::update(){
    // if(isEnablingAnimationStarted) {
    //     if(buttonIcon.getX() < enabledX) {
    //         buttonIcon.setLastXandY(buttonIcon.getX(), buttonIcon.getY());
    //         buttonIcon.moveBy(2, 0);
    //         isRenderNeeded = true;
    //     }
    //     else {
    //         isEnablingAnimationStarted = false;
    //     }
    // }
    // if(isDisablingAnimationStarted) {
    //     if(buttonIcon.getX() > disabledX) {
    //         buttonIcon.setLastXandY(buttonIcon.getX(), buttonIcon.getY());
    //         buttonIcon.moveBy(-2, 0);
    //         isRenderNeeded = true;
    //     }
    //     else {
    //         isDisablingAnimationStarted = false;
    //     }
    // }
}

void Slider::touchInput(int x, int y) {
    hitbox.touchInput(x, y);
}