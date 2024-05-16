#include "app/settings/subsystemInspector.hpp"
#include "os/portableos.hpp"


void SubsystemInspector::readSubsystemData()
{
    SubsystemOverview newOverview = OS_API::getSubsystemOverview();

    if(newOverview.isCommunicating == currentOverview.isCommunicating &&
        newOverview.data.isWiFiConnectedFlag == currentOverview.data.isWiFiConnectedFlag &&
        newOverview.data.wasWiFiRequestedFlag == currentOverview.data.wasWiFiRequestedFlag &&
        newOverview.credentials.ssid == currentOverview.credentials.ssid &&
        newOverview.credentials.password == currentOverview.credentials.password
    ){
        isNewOverviewReceived = false;
    }else 
    {
        currentOverview = newOverview;
        isNewOverviewReceived = true;
    }
}

SubsystemInspector::SubsystemInspector() {
    readSubsystemData();
}

void SubsystemInspector::udpDataReceived(int messageID, std::vector<uint8_t> data) {

}

SubsystemInspector::~SubsystemInspector() {

}


void SubsystemInspector::start(int w, int h){ 

}


void SubsystemInspector::longPressInput(InputType input)
{

}

void SubsystemInspector::longPressRelease(InputType input)
{

}

void SubsystemInspector::analogInput(int x, int y) {

}

void SubsystemInspector::input(InputType input) {

}


void SubsystemInspector::touchInput(int x, int y) {

}

void SubsystemInspector::update(){
    readSubsystemData();
}

void SubsystemInspector::render(DisplayProvider& display){
    if(isNewOverviewReceived)
    {

        display.fillScreen(TFT_WHITE);
        display.setTextColor(TFT_BROWN, TFT_WHITE);
        display.drawString("Subsystem Inspector", 130, 10);
        display.setTextColor(TFT_BLACK, TFT_WHITE);


        display.drawString("Communicating : ", 20, 50);
        if(currentOverview.isCommunicating)
        {
            display.setTextColor(TFT_GREEN, TFT_WHITE);
            display.drawString("True", 290, 50);
        }else
        {
            display.setTextColor(TFT_RED, TFT_WHITE);
            display.drawString("False", 290, 50);
        }
        display.setTextColor(TFT_BLACK, TFT_WHITE);



        display.drawString("WiFi requested : ", 20, 80);
        if(currentOverview.data.wasWiFiRequestedFlag)
        {
            display.setTextColor(TFT_GREEN, TFT_WHITE);
            display.drawString("True", 290, 80);
        }else
        {
            display.setTextColor(TFT_RED, TFT_WHITE);
            display.drawString("False", 290, 80);
        }
        display.setTextColor(TFT_BLACK, TFT_WHITE);




        display.drawString("WiFi connected : ", 20,110);
        if(currentOverview.data.isWiFiConnectedFlag)
        {
            display.setTextColor(TFT_GREEN, TFT_WHITE);
            display.drawString("True", 290, 110);
        }else
        {
            display.setTextColor(TFT_RED, TFT_WHITE);
            display.drawString("False", 290, 110);
        }
        display.setTextColor(TFT_BLACK, TFT_WHITE);


        // Only show when WiFi is connected
        if(currentOverview.data.isWiFiConnectedFlag){
            display.drawString("SSID : ", 20, 140);
            display.drawString(String(currentOverview.credentials.ssid), 100, 140);

            display.drawString("Password : ", 20, 170);
            display.drawString(String(currentOverview.credentials.password), 150, 170);

            display.drawString("IP Address : ", 20, 200);
            display.drawString(String(currentOverview.data.ipOctet1) + "." + String(currentOverview.data.ipOctet2) + "." + String(currentOverview.data.ipOctet3) + "." + String(currentOverview.data.ipOctet4),
            155, 200);

        }
    }
    
}

void SubsystemInspector::end(){ 

}


String SubsystemInspector::getAppNameString()
{
    return "Ustawienia";
}

uint16_t SubsystemInspector::getBackgroundColor(){
    return TFT_BLACK;
}
