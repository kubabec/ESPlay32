#include "app/settings/wifiListConnector.hpp"
#include "os/portableos.hpp"


std::vector<String> networks = {"UPC5284544", "Kuba", "Marcel telefon", "Kuba iPhone"};

WiFiListConnector::WiFiListConnector() {
    networkConnectionMenu = new Menu(networks);

    networkConnectionMenu->registerChoiceDonePollValue(&networkSelection);
}

void WiFiListConnector::udpDataReceived(int messageID, std::vector<uint8_t> data) {

}

WiFiListConnector::~WiFiListConnector() {
    delete networkConnectionMenu;
}


void WiFiListConnector::start(int w, int h){ 
    if(networkConnectionMenu != nullptr)
    {
        networkConnectionMenu->requestActivation();
    }
}


void WiFiListConnector::longPressInput(InputType input)
{

}

void WiFiListConnector::longPressRelease(InputType input)
{

}

void WiFiListConnector::analogInput(int x, int y) {
    networkConnectionMenu->analogInput(x, y);
}

void WiFiListConnector::input(InputType input) {
    networkConnectionMenu->input(input);
}


void WiFiListConnector::touchInput(int x, int y) {

}

void WiFiListConnector::update(){
    networkConnectionMenu->update();

    if(networkSelection != -1) {
        switch(networkSelection) {
            case 0: // UPC5284544
                OS_API::connectToNetwork("UPC5284544", "ySumyhcePuz8");
            break;
            case 1: // Kuba
                OS_API::connectToNetwork("Orange_Swiatlowod_DA2C", "2FYXFG6MAGVZ");
            break;
            case 2: // nie, po prostu nie
                OS_API::connectToNetwork("nie, po prostu nie", "hmmmmmmm");
            break;
            case 3: // nie, po prostu nie
                OS_API::connectToNetwork("iPhone (Kuba)", "esplay32");
            break;
            default:
            break;
        }
        networkSelection = -1;
        connectionRequested = true;
    }
}

void WiFiListConnector::render(DisplayProvider& display){
    if(connectionRequested)
    {
        display.fillScreen(TFT_BLACK);
        display.setTextColor(TFT_WHITE, TFT_BLACK);
        display.drawString("Connection in progress... Exit with 'D'", 20, 100);
    }else 
    {
        if(!isLoaded)
        {
            display.fillScreen(TFT_BLACK);
            isLoaded = true;
        }
        networkConnectionMenu->render(display);
    }
    
}

void WiFiListConnector::end(){ 

}


String WiFiListConnector::getAppNameString()
{
    return "Ustawienia";
}

uint16_t WiFiListConnector::getBackgroundColor(){
    return TFT_BLACK;
}
