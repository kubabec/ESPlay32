#include "app/ledCommunicator.hpp"

LedCommunicator::LedCommunicator() : 
buttonEn1(85, 250, 1, std::bind(&LedCommunicator::callback, this, std::placeholders::_1, std::placeholders::_2)),
buttonEn2(355, 250, 2, std::bind(&LedCommunicator::callback, this, std::placeholders::_1, std::placeholders::_2)),
slider1(30, 50,  1, std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)),
slider2(30, 120,  2, std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)),
slider3(30, 190,  3, std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)),
slider4(300, 50,  4, std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)),
slider5(300, 120,  5, std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)),
slider6(300, 190,  6, std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)),
brightnessSlider(155, 250,  7, std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2))
{
    touchSliders.push_back(&slider1);
    touchSliders.push_back(&slider2);
    touchSliders.push_back(&slider3);
    touchSliders.push_back(&slider4);
    touchSliders.push_back(&slider5);
    touchSliders.push_back(&slider6);
    touchSliders.push_back(&brightnessSlider);
    messageContent.ledZero = {255, 255, 255};
    messageContent.ledOne = {255, 255, 255};
}

void LedCommunicator::start(int w, int h){

}

void LedCommunicator::input(InputType input){ 
    
}

void LedCommunicator::udpDataReceived(int messageID, std::vector<uint8_t> data) {

}

void LedCommunicator::updateLedShieldData(LedMessageContent& msg) {
    MessageUDP updateMessage(150, {192, 168, 0, 255}, 9001);
    updateMessage.pushData((byte*)&msg, sizeof(msg));
    OS_API::sendUdpBroadcastMessage(updateMessage);
}

void LedCommunicator::longPressInput(InputType input)
{

}

void LedCommunicator::longPressRelease(InputType input)
{

}

void LedCommunicator::analogInput(int x, int y) {

}

void LedCommunicator::touchInput(int x, int y) {
    buttonEn1.touchInput(x, y);
    buttonEn2.touchInput(x, y);

    for(Slider* sliderPtr: touchSliders)
    {
        sliderPtr->touchInput(x, y);
    }
}

void LedCommunicator::update(){
    buttonEn1.update();
    buttonEn2.update();
    for(Slider* sliderPtr: touchSliders)
    {
        sliderPtr->update();
    }

}

void LedCommunicator::render(DisplayProvider& display){
    
    for(Slider* sliderPtr: touchSliders)
    {
        sliderPtr->draw(display);
    }

    buttonEn1.draw(display);
    buttonEn2.draw(display);

    if(isRenderNeeded)
    {
        display.setTextColor(TFT_YELLOW, TFT_BLACK);
        display.drawString("LED 1", 75, 15);
        display.drawString("LED 2", 345, 15);

        display.setTextColor(TFT_RED, TFT_BLACK);
        display.drawString("RED", 210, 55);
        display.setTextColor(TFT_GREEN, TFT_BLACK);
        display.drawString("GREEN", 195, 125);
        display.setTextColor(TFT_BLUE, TFT_BLACK);
        display.drawString("BLUE", 200, 195);
        isRenderNeeded = false;
    }

}

void LedCommunicator::forceRender(DisplayProvider &display)
{

}


void LedCommunicator::end(){ 

}

String LedCommunicator::getAppNameString()
{
    return "LedCommunicator";
}

uint16_t LedCommunicator::getBackgroundColor(){
    return TFT_BLACK;
}

void LedCommunicator::callback(int buttonId, bool isOn) {
    if (buttonId == 1) {
        isOneOff = !isOn;
    }
    else if (buttonId == 2) {
        isSndOff = !isOn;
    }
    LedMessageContent finalMessage = messageContent;
    if(isOneOff) {
        finalMessage.ledZero = {0};
    }
    if(isSndOff) {
        finalMessage.ledOne = {0};
    }
    updateLedShieldData(finalMessage);
}

void LedCommunicator::sliderCallback(int sliderId, int value) {
    //Serial.println("Received value : " + String(value) + " from slider ID " + String(sliderIdentifier));
    int newValue = 0;
    if(value <= 15) {
        newValue = 0;
    }
    else {
        newValue = value;
    }
    switch(sliderId) {
        case 1:
            messageContent.ledZero.r = newValue;
        break;
        case 2:
            messageContent.ledZero.g = newValue;
        break;
        case 3:
            messageContent.ledZero.b = newValue;
        break;
        case 4:
            messageContent.ledOne.r = newValue;
        break;
        case 5:
            messageContent.ledOne.g = newValue;
        break;
        case 6:
            messageContent.ledOne.b = newValue;
        break;
        case 7:
            messageContent.brightness = (uint8_t)((float)value / 2.55f);
            if(messageContent.brightness <= 10) {
                messageContent.brightness = 0;
            }
        break;
        
        default:

        break;
    }
    LedMessageContent finalMessage = messageContent;
    if(isOneOff) {
        finalMessage.ledZero = {0};
    }
    if(isSndOff) {
        finalMessage.ledOne = {0};
    }
    updateLedShieldData(finalMessage);
}
