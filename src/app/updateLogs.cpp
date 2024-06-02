#include "app/UpdateLogs.hpp"

UpdateLogs::UpdateLogs() {

}

void UpdateLogs::start(int w, int h){ 
    
}

void UpdateLogs::input(InputType input){ 
    switch(input) {
        case BUTTON_A:
        if(firstChosenUpdate > 0) {
            firstChosenUpdate--;
            refreshNeeded = true;
        }
        break;
        case BUTTON_C:
        if(firstChosenUpdate < 5) {
            firstChosenUpdate++;
            refreshNeeded = true;
        }
        break;
        default:
        break;
    }
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
    if(refreshNeeded) {
        display.fillRect(25, 50, 480, 125, TFT_BLACK);
        refreshNeeded = false;
    }
    display.drawString("latest updates", 25, 0);
    display.drawString(logs[firstChosenUpdate + 0], 25, 50);
    display.drawString(logs[firstChosenUpdate + 1], 25, 75);
    display.drawString(logs[firstChosenUpdate + 2], 25, 100);
    display.drawString(logs[firstChosenUpdate + 3], 25, 125);
    display.drawString(logs[firstChosenUpdate + 4], 25, 150);                                                                                                                                                                                                               //ḃ̵̯͋o̷̟̲̒̋̀b̷̭͌̆ ̶̡̳̌͝r̵̼̣͊͆̇̀̊e̴̡̛̘̎̓ä̴̖́͗̓̉̔l̴̛̼̐̐̍͛l̶̖̦̅y̸̟̳̱͖̼̎̂͊̐ ̷̡͚͔̔̈̅͒l̵̢̨̛͖̝͝i̶̝̖̻͈̿͑͂͠k̸͈͚̥͚̂̆e̶̦̓́̈̍š̷͈͇̟͑̄̒͝ͅ ̴̖̂͒̆͌s̶͙̩̹̎͒͘p̴̘̀ả̸̛̼̙̰ģ̷̝̜̹̑͐͂̔h̷͔̰̱̬͚̽͛ẻ̸͖̥̼̅͌̍͘͜ṫ̷̰̳̬̗̅̂́͝t̵͉̪͍͛̌͝į̴̲̮͎̼̑ ̶̳̲̱̙̳̂̈́͋̌͘c̷̙̲̹̞͇͛̄̓o̵̫͙͂͐͛d̷͕̦̪̀e̸̢̢̜͔͘
    display.drawString("press a to go up", 25, 200);
    display.drawString("press c to go down", 25, 225);
}

void UpdateLogs::forceRender(DisplayProvider &display)
{

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
