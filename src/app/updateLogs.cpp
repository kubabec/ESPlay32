#include "app/UpdateLogs.hpp"

UpdateLogs::UpdateLogs() {

}

void UpdateLogs::start(int w, int h){ 
    
}

void UpdateLogs::input(InputType input){ 
    
}

void UpdateLogs::udpDataReceived(int messageID, std::vector<uint8_t> data) {

}

void UpdateLogs::longPressInput(InputType input)
{

}

void UpdateLogs::longPressRelease(InputType input)
{

}

void UpdateLogs::analogInput(int x, int y) {

}

void UpdateLogs::touchInput(int x, int y) {

}

void UpdateLogs::update(){

}

void UpdateLogs::render(DisplayProvider& display){
    display.drawString("Update 21.05.2024 (update logs update)", 25, 25);
    display.drawString("Added:", 25, 50);
    display.drawString("- Update logs", 25, 75);
}

void UpdateLogs::end(){ 

}

String UpdateLogs::getAppNameString()
{
    return "Update Logs";
}

uint16_t UpdateLogs::getBackgroundColor(){
    return TFT_BLACK;
}
