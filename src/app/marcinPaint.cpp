#include "app/marcinPaint.hpp"

MarcinPaint::MarcinPaint() {

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
    this->x += x;
    this->y -= y;
}

void MarcinPaint::touchInput(int x, int y) {
    this->x = x;
    this->y = y;
}

void MarcinPaint::update() {

}

void MarcinPaint::render(DisplayProvider& display){

    display.fillCircle(x, y, 10, ballCol);
    if (clearScreen){
        MarcinPaint::createMenu(display);
        clearScreen = false; 
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


void MarcinPaint::paintShape(DisplayProvider &display) {
    display.fillCircle(30, 50, 20, TFT_RED);
}

void MarcinPaint::paintSize(DisplayProvider &display) {
    display.fillRect(10, 130, 40, 3, TFT_BLACK);
    display.fillRect(10, 140, 40, 10, TFT_BLACK);
}

void MarcinPaint::paintColor(DisplayProvider &display) {
    display.fillRect(10, 220, 40, 10, TFT_GREEN);
    display.fillRect(10, 230, 40, 10, TFT_BLUE);
    display.fillRect(10, 240, 40, 10, TFT_YELLOW);
    display.fillRect(10, 250, 40, 10, TFT_ORANGE);
}

void MarcinPaint::createMenu(DisplayProvider &display) {
    display.fillScreen(TFT_WHITE);
    paintShape(display);
    paintSize(display);
    paintColor(display);
}