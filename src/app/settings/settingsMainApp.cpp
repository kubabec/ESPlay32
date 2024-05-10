#include "app/settings/settingsMainApp.hpp"
#include "app/settings/subsystemInspector.hpp"
#include "app/settings/wifiListConnector.hpp"
#include "os/portableos.hpp"

std::vector<String> menuOptions = {"Subsystem inspector", "Polacz do sieci", "Kolor zaznaczenia", "Kolor tla", "Kolor motywu"};
std::vector<String> colors = {"Niebieski", "Zielony", "Pomaranczowy", "Czarny", "Bialy", "Czerwony"};

uint32_t colorMapping[6]
{
    TFT_BLUE,
    TFT_GREENYELLOW,
    TFT_ORANGE,
    TFT_BLACK,
    TFT_WHITE,
    TFT_RED
};

Settings::Settings() {
    settingsMainMenu = new Menu(menuOptions);
    // colorSelectionMenu = new Menu(colors);
    // networkConnectionMenu = new Menu(networks);

    settingsMainMenu->registerChoiceDonePollValue(&submenuSelection);
    // colorSelectionMenu->registerChoiceDonePollValue(&colorSelection);
    // networkConnectionMenu->registerChoiceDonePollValue(&networkSelection);
}

void Settings::udpDataReceived(int messageID, std::vector<uint8_t> data) {

}

Settings::~Settings() {
    delete settingsMainMenu;
    // delete colorSelectionMenu;
    // delete networkConnectionMenu;
}

void Settings::checkSelections()
{
    if(submenuSelection != -1 && currentState == SETTINGS_MENU)
    {
        currentState = (SettingState)(submenuSelection+1);

        switch(currentState)
        {
            case SETTINGS_SUBSYSTEM_INSPECTOR:
                subApp = new SubsystemInspector();
                break;
            case SETTINGS_NETWORK_CONNECTION_MENU:
                // Network connection only allowed when subsystem is communicating
                if(OS_API::getSubsystemOverview().isCommunicating){
                    subApp = new WiFiListConnector();
                }else 
                {
                    currentState = SETTINGS_MENU;
                }
                break;

            default:
                currentState = SETTINGS_MENU;
            break;
        }
               

        submenuSelection = -1;
        // Serial.println("wrong case");
        // currentState = (SettingState)(submenuSelection+1);
        // if(currentState != SETTINGS_SUBSYSTEM_INSPECTOR){
        //     if(currentState == SETTINGS_NETWORK_CONNECTION_MENU) {
        //         networkConnectionMenu->requestActivation();
        //     }
        //     else{
        //         colorSelectionMenu->requestActivation();
        //     }
            
        //     submenuSelection = -1;
        //     colorSelection = -1;
        //     networkSelection = -1;
        // }
    }

    // if(colorSelection != -1 &&(currentState != SETTINGS_MENU && currentState != SETTINGS_NETWORK_CONNECTION_MENU))
    // {
    //     switch (currentState)
    //     {
    //     case SETTINGS_SELECTION_COLOR_MENU:
    //         PortableOS::setSystemColor(SystemColor::SELECTION_COLOR, colorMapping[colorSelection]);
    //         break;
        
    //     case SETTINGS_BG_COLOR_MENU:
    //         PortableOS::setSystemColor(SystemColor::BG_COLOR, colorMapping[colorSelection]);
    //         break;

    //     case SETTINGS_MOTIVE_COLOR_MENU:
    //         PortableOS::setSystemColor(SystemColor::MOTIVE_COLOR, colorMapping[colorSelection]);
    //         break;

    //     default:
    //         break;
    //     }

    //     currentState = SETTINGS_MENU;
    //     colorSelection = -1;
    //     submenuSelection = -1;
    //     settingsMainMenu->requestActivation();
    // }

    // if(networkSelection != -1 && currentState == SETTINGS_NETWORK_CONNECTION_MENU) {
    //     switch(networkSelection) {
    //         case 0: // UPC5284544
    //             OS_API::connectToNetwork("monke", "banana");
    //         break;
    //         case 1: // Kuba
    //             OS_API::connectToNetwork("Orange_Swiatlowod_DA2C", "2FYXFG6MAGVZ");
    //         break;
    //         case 2: // nie, po prostu nie
    //             OS_API::connectToNetwork("123", "456");
    //         break;
    //         default:
    //         break;
    //     }

    //     currentState = SETTINGS_MENU;
    //     networkSelection = -1;
    //     submenuSelection = -1;
    //     settingsMainMenu->requestActivation();
    // }
}

void Settings::start(int w, int h){ 
    if(settingsMainMenu != nullptr)
    {
        settingsMainMenu->requestActivation();
    }
}

void Settings::input(InputType input){ 
    // if(currentState != SETTINGS_SUBSYSTEM_INSPECTOR){
    //     if(currentState == SETTINGS_MENU)
    //     {
    //         if(settingsMainMenu != nullptr)
    //         {
    //             settingsMainMenu->input(input);
    //         }
    //     }else if (currentState == SETTINGS_NETWORK_CONNECTION_MENU) {
    //         networkConnectionMenu->input(input);
    //     }else
    //     {
    //         colorSelectionMenu->input(input);
    //     }
    // }

    if(currentState == SETTINGS_MENU)
    {
        if(settingsMainMenu != nullptr)
            {
                settingsMainMenu->input(input);
            }
    }else
    {

        if(subApp != nullptr){
            // Exit subApp
            if(input == BUTTON_D)
            {
                subApp->end();
                delete subApp;
                subApp = nullptr; 
                currentState = SETTINGS_MENU;
                if(settingsMainMenu != nullptr)
                {
                    settingsMainMenu->requestActivation();
                }
            }else 
            {
                subApp->input(input);
            }
        }
    }
}


void Settings::longPressInput(InputType input)
{

}

void Settings::longPressRelease(InputType input)
{

}

void Settings::analogInput(int x, int y) {
    // if(currentState != SETTINGS_SUBSYSTEM_INSPECTOR){
    //     if(currentState == SETTINGS_MENU)
    //     {
    //         if(settingsMainMenu != nullptr)
    //         {
    //             settingsMainMenu->analogInput(x,y);
    //         }
    //     }else if (currentState == SETTINGS_NETWORK_CONNECTION_MENU) {
    //         networkConnectionMenu->analogInput(x, y);
    //     }else
    //     {
    //         colorSelectionMenu->analogInput(x, y);
    //     }
    // }

    if(currentState == SETTINGS_MENU)
    {
        if(settingsMainMenu != nullptr)
            {
                settingsMainMenu->analogInput(x,y);
            }
    }else
    {
        if(subApp != nullptr)
        {
            subApp->analogInput(x,y);
        }
    }
}

void Settings::touchInput(int x, int y) {

}

void Settings::update(){
    // settingsMainMenu->update();
    // colorSelectionMenu->update();
    // networkConnectionMenu->update();

    // checkSelections();
    // if(currentState == SETTINGS_SUBSYSTEM_INSPECTOR)
    // {
    //     static long timer200 = 0;

    //     if(millis() - timer200 > 200){
    //         currentOverview = OS_API::getSubsystemOverview();
    //         timer200 = millis();
    //     }
        
    // }

    if(currentState == SETTINGS_MENU)
    {
        settingsMainMenu->update();
        checkSelections();
    }else
    {
        if(subApp != nullptr)
        {
            subApp->update();
        }
    }
}

void Settings::render(DisplayProvider& display){
    // if(currentState == SETTINGS_MENU)
    // {
    //     if(settingsMainMenu != nullptr)
    //     {
    //         settingsMainMenu->render(display);
    //     }
    // }else if(currentState == SETTINGS_NETWORK_CONNECTION_MENU) {
    //     networkConnectionMenu->render(display);
    // }else if(currentState == SETTINGS_SUBSYSTEM_INSPECTOR)
    // {
    //     static long timer200 = 0;

    //     if(millis() - timer200 > 200){
    //         display.fillScreen(TFT_DARKGREY);
    //         display.setTextColor(TFT_BLACK, TFT_DARKGREY);
    //         display.drawString("isCommunicating : ", 20, 20);
    //         display.drawString(String(currentOverview.isCommunicating), 290, 20);

    //         display.drawString("connection requested : ", 20, 50);
    //         display.drawString(String(currentOverview.data.wasWiFiRequestedFlag), 290, 50);

    //         display.drawString("WiFi connected : ", 20, 80);
    //         display.drawString(String(currentOverview.data.isWiFiConnectedFlag), 290, 80);

    //         display.drawString("SSID : ", 20, 110);
    //         display.drawString(String(currentOverview.data.lastConnectedSSID), 100, 110);

    //         display.drawString("Password : ", 20, 140);
    //         display.drawString(String(currentOverview.data.lastConnectedPassword), 150, 140);

    //         timer200 = millis();
    //     }
    // }
    // else
    // {
    //     colorSelectionMenu->render(display);
    // }

    if(currentState == SETTINGS_MENU)
    {
        if(settingsMainMenu != nullptr)
        {
            settingsMainMenu->render(display);
        }
    }else 
    {
        if(subApp != nullptr)
        {
            subApp->render(display);
        }
    }
}

void Settings::end(){ 

}


String Settings::getAppNameString()
{
    return "Ustawienia";
}

uint16_t Settings::getBackgroundColor(){
    return TFT_BLACK;
}
