#include "os/services/notificationService.hpp"

NotificationService::NotificationService() {

}

void NotificationService::start(int w, int h){ 
    
}

void NotificationService::input(InputType input){ 
    
}

void NotificationService::udpDataReceived(int messageID, std::vector<uint8_t> data) {

}

void NotificationService::longPressInput(InputType input)
{

}

void NotificationService::longPressRelease(InputType input)
{

}

void NotificationService::analogInput(int x, int y) {

}

void NotificationService::touchInput(int x, int y) {

}

void NotificationService::update(){

}

void NotificationService::render(DisplayProvider& display){

}

void NotificationService::end(){ 

}

String NotificationService::getAppNameString()
{
    return "NotificationService";
}

uint16_t NotificationService::getBackgroundColor(){
    return TFT_RED;
}

bool NotificationService::isContextTakenOver() {
    return false;
}

void NotificationService::pushNotification(Notification& notif) {

}