#include "app/marcinApp.hpp"

MarcinApp::MarcinApp() {

}

void MarcinApp::start(int w, int h){ 
    x = 200;
    y = 180;
}

void MarcinApp::input(InputType input){ 
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
            changeScreenColour = true;
            backgroundcolor = colours[indexColour];
            indexColour++;
                if(indexColour >= 5){
                    indexColour = 0;
                }
            break;
        // case BUTTON_B:
        //     // changeBallColour = true;
        //     ballCol = ballColours[indexColour];
        //     indexColour++;
        //         if(indexColour >=5){
        //             indexColour =0;
        //         }
        //     break;
    }

}

void MarcinApp::udpDataReceived(int messageID, std::vector<uint8_t> data) {

}

void MarcinApp::longPressInput(InputType input){
       
         Serial.println("Long pressed!!!!");
}

void MarcinApp::longPressRelease(InputType input){

}

void MarcinApp::analogInput(int x, int y) 
{
    this->x += x;
    this->y -= y;
}

void MarcinApp::touchInput(int x, int y) {
    this->x = x;
    this->y = y;
}

void MarcinApp::update() {

}

void MarcinApp::render(DisplayProvider& display){

        // display.fillCircle(x, y, 10, ballCol);
    if (changeScreenColour){
        display.fillScreen(backgroundcolor);
        changeScreenColour = false; 
    }
    drawGameboardBg(display);
}

void MarcinApp::forceRender(DisplayProvider &display)
{

}

void MarcinApp::end(){ 

}


String MarcinApp::getAppNameString()
{
    return "MarcinApp";
}

uint16_t MarcinApp::getBackgroundColor(){

    return TFT_YELLOW;
}

void MarcinApp::drawGameboardBg(DisplayProvider &display)
{
    int startXVertical = 210;               
    int startYHorizontal = 15;  
    int startX = 210;
    int startY = 15;               

    for(int i = 0; i < numberOfLines; i++) {
        display.fillRect(startXVertical, startY, lengthVertical, heightVertical, TFT_WHITE); // lines |
        display.fillRect(startX, startYHorizontal, lengthHorizontal, heightHorizontal, TFT_WHITE); // lines -
        startXVertical += horizontalFieldWidth + 3;
        startYHorizontal += horizontalFieldWidth +3;
    }
    isBgDrawn = true;
}
