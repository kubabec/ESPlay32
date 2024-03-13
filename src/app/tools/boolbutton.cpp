#include <app/tools/boolbutton.hpp>


BoolButton::BoolButton(uint16_t ax, uint16_t ay) : x(ax), y(ay) {
    hitbox.addTouchArea(x, y, w, h,
    std::bind(&BoolButton::switchButton, this));
    disabledX = (x + (w / 4));
    enabledX = x + (w / 2 + w / 4);
    buttonIcon.setColor(TFT_RED);
    buttonIcon.move(disabledX, (y + (h / 2)));
    buttonIcon.setLastXandY(buttonIcon.getX(), buttonIcon.getY());
    buttonIcon.setBgColor(TFT_WHITE);
}

void BoolButton::switchButton() {  
    if (!isOn) {
        isEnablingAnimationStarted = true;
    }
    else {
        isDisablingAnimationStarted = true;
    }
    isOn = !isOn;
}

void BoolButton::draw(DisplayProvider &display) {
    if (!isRectangleDrawn) {
        display.fillRect(x - 2, y - 2, w + 4, h + 4, TFT_BLUE);
        display.fillRect(x - 1, y - 1, w + 2, h + 2, TFT_WHITE);

        isRectangleDrawn = true;
    }
    if (isRenderNeeded) {
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

void BoolButton::update(){
    if(isEnablingAnimationStarted) {
        if(buttonIcon.getX() < enabledX) {
            buttonIcon.setLastXandY(buttonIcon.getX(), buttonIcon.getY());
            buttonIcon.moveBy(2, 0);
            isRenderNeeded = true;
        }
        else {
            isEnablingAnimationStarted = false;
        }
    }
    if(isDisablingAnimationStarted) {
        if(buttonIcon.getX() > disabledX) {
            buttonIcon.setLastXandY(buttonIcon.getX(), buttonIcon.getY());
            buttonIcon.moveBy(-2, 0);
            isRenderNeeded = true;
        }
        else {
            isDisablingAnimationStarted = false;
        }
    }
}

void BoolButton::touchInput(int x, int y) {
    if (!isEnablingAnimationStarted || !isDisablingAnimationStarted) {
        hitbox.touchInput(x, y);
    }
}