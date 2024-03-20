#include <app/ledCommunicator.hpp>

LedCommunicator::LedCommunicator() : testButton(100, 100, std::bind(&LedCommunicator::callback, this, std::placeholders::_1)),
testSlider(200, 50, std::bind(&LedCommunicator::sliderCallback, this, std::placeholders::_1)){

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
    testButton.touchInput(x, y);
    testSlider.touchInput(x, y);
}

void LedCommunicator::update(){
    testButton.update();
    testSlider.update();
}

void LedCommunicator::render(DisplayProvider& display){
    testButton.draw(display);
    if(callbackTest) {
        callbackTest = false;
        display.fillCircle(69, 31, 27, 510);
    }
    if(callbackTestTwo) {
        callbackTestTwo = false;
        display.fillCircle(100, 200, 27, 510);
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
    if(isOn) {
        callbackTest = true;
    }
    else {
        callbackTestTwo = true;
    }
}

void LedCommunicator::sliderCallback(int value) {
    
}
