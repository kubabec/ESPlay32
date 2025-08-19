#include "app/marcinPaint.hpp"

MarcinPaint::MarcinPaint() {
vec_buttons.emplace_back(10,10,75,40,"shape");
vec_buttons.emplace_back(10,120,75,40,"size");
vec_buttons.emplace_back(10,240,75,40,"color");
}

void MarcinPaint::start(int w, int h){ 
    x = 200;
    y = 180;
}

void MarcinPaint::input(InputType input){ 
    switch(input){
        case BUTTON_A:
            y -= 5;    
            break;
        case BUTTON_C:
            y += 5;
            break;
        case BUTTON_D:
            x -= 5;
            break;
        case BUTTON_B:
            x += 5;
            break;
        case BUTTON_K:
            clearScreen = true;
            backgroundcolor = TFT_WHITE;
            break;
    }

}

void MarcinPaint::udpDataReceived(int messageID, std::vector<uint8_t> data) {

}

void MarcinPaint::longPressInput(InputType input){
       
         Serial.println("Long pressed!!!!");
}

void MarcinPaint::longPressRelease(InputType input){

}

void MarcinPaint::analogInput(int x, int y) 
{

}

void MarcinPaint::touchInput(int touch_x, int touch_y) {
    if (touch_x >= 120) {
        drawingPoints.push_back({touch_x, touch_y});
    }
    x = touch_x;
    y = touch_y;
    // Process touch input areas for buttons
    for (auto& btn : vec_buttons) {
        btn.touchArea(x, y);
    }
}

void MarcinPaint::update() {
    
}

void MarcinPaint::render(DisplayProvider& display){

    if (clearScreen) {
        for(auto &btn : vec_buttons){
            btn.needsRedraw = true;
        }
        display.fillScreen(backgroundcolor);  // Clear the whole screen or background
        clearScreen = false;
    }

    // Draw all the points in your stroke (painting area)
    for (auto& pt : drawingPoints) {
        display.fillCircle(pt.x, pt.y, 10, ballCol); 
    }
    drawingPoints.clear();

    // Always draw buttons (to avoid flicker)
    if(!isDrawing){
        for (auto& btn : vec_buttons) {
            btn.drawButton(display);
        }
    }
    
}
void MarcinPaint::forceRender(DisplayProvider &display)
{

}

void MarcinPaint::end(){ 
    
}


String MarcinPaint::getAppNameString()
{
    return "MarcinPaint";
}

uint16_t MarcinPaint::getBackgroundColor(){

    return TFT_WHITE;
}
