#include <app/ledCommunicator.hpp>

LedCommunicator::LedCommunicator() {

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
}

void LedCommunicator::update(){

}

void LedCommunicator::render(DisplayProvider& display){
    testButton.draw(display);
}

void LedCommunicator::end(){ 

}

String LedCommunicator::getAppNameString()
{
    return "LedCommunicator";
}

uint16_t LedCommunicator::getBackgroundColor(){
    return TFT_LIGHTGREY;
}
