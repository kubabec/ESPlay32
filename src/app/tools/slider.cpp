#include "app/tools/slider.hpp"



Slider::Slider(uint16_t ax, uint16_t ay, int asliderID, std::function<void (int, int)> acallback) : 
x(ax), 
y(ay),
sliderID(asliderID),
callbackOnStatusChange(acallback), 
hitbox(x, y, w, h, 255, std::bind(&Slider::sliderValueChange, this, std::placeholders::_1))
{
    buttonIcon.setColor(TFT_BLUE);
    buttonIcon.move(ax + w, (y + (h / 2)));
    buttonIcon.setLastXandY(buttonIcon.getX(), buttonIcon.getY());
    buttonIcon.setBgColor(TFT_BLACK);
}

void Slider::sliderValueChange(int value) { 
    float newX; 
    //Serial.println("New value received!");
    if(callbackOnStatusChange){
        callbackOnStatusChange(sliderID, value);
    }
    newX = value * w / 255.f;
    newX += x;
    // Serial.println("new value: " + (String(newX)));
    buttonIcon.setLastXandY(buttonIcon.getX(), buttonIcon.getY());
    buttonIcon.move(newX, buttonIcon.getY());
    isRenderNeeded = true;
}

void Slider::draw(DisplayProvider &display) {
    if (isRenderNeeded) {
        display.fillCircle(buttonIcon.getLastX(), buttonIcon.getY(), h/2, TFT_BLACK);
        display.fillRect(x, y + 10, w, h - 20, TFT_WHITE);
        display.fillCircle(buttonIcon.getX(), buttonIcon.getY(), h/2, TFT_BLUE);


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
}

void Slider::touchInput(int x, int y) {
    hitbox.touchInput(x, y);
}