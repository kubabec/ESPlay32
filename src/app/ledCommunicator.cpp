#include <app/ledCommunicator.hpp>

LedCommunicator::LedCommunicator() : 
buttonEn1(85, 250, std::bind(&LedCommunicator::callback, this, std::placeholders::_1)),
buttonEn2(355, 250, std::bind(&LedCommunicator::callback, this, std::placeholders::_1)),
slider1(30, 50,  1, std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)),
slider2(30, 120,  1, std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)),
slider3(30, 190,  1, std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)),
slider4(300, 50,  1, std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)),
slider5(300, 120,  1, std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)),
slider6(300, 190,  1, std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2))
{
    touchSliders.push_back(&slider1);
    touchSliders.push_back(&slider2);
    touchSliders.push_back(&slider3);
    touchSliders.push_back(&slider4);
    touchSliders.push_back(&slider5);
    touchSliders.push_back(&slider6);
    // touchSliders.push_back(
    //     std::move(Slider(
    //         50, // x
    //         150,  // y
    //         2,  // Identifier
    //         std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1))));

    // touchSliders.push_back(
    //     Slider(
    //         50, // x
    //         150,  // y
    //         2,  // Identifier
    //         std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)));

    // touchSliders.push_back(
    //     Slider(
    //         50, // x
    //         250,  // y
    //         3,  // Identifier
    //         std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)));

    // touchSliders.push_back(
    //     Slider(
    //         250, // x
    //         50,  // y
    //         4,  // Identifier
    //         std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)));

    // touchSliders.push_back(
    //     Slider(
    //         250, // x
    //         150,  // y
    //         5,  // Identifier
    //         std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)));

    // touchSliders.push_back(
    //     Slider(
    //         250, // x
    //         250,  // y
    //         6,  // Identifier
    //         std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1, std::placeholders::_2)));
}

void LedCommunicator::start(int w, int h){

}

void LedCommunicator::input(InputType input){ 
    
}

void LedCommunicator::udpDataReceived(int messageID, std::vector<uint8_t> data) {

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

void LedCommunicator::end(){ 

}

String LedCommunicator::getAppNameString()
{
    return "LedCommunicator";
}

uint16_t LedCommunicator::getBackgroundColor(){
    return TFT_BLACK;
}

void LedCommunicator::callback(bool isOn) {

}

void LedCommunicator::sliderCallback(int sliderId, int value) {
    //Serial.println("Received value : " + String(value) + " from slider ID " + String(sliderIdentifier));
}
