#include "app/settingsapp.hpp"
#include "os/portableos.hpp"

std::vector<String> menuOptions = {"Kolor zaznaczenia", "Kolor tla", "Kolor motywu", "Polacz do sieci"};
std::vector<String> colors = {"Niebieski", "Zielony", "Pomaranczowy", "Czarny", "Bialy", "Czerwony"};
std::vector<String> networks = {"UPC5284544", "Kuba", "nie, po prostu nie"};

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
    colorSelectionMenu = new Menu(colors);
    networkConnectionMenu = new Menu(networks);

    settingsMainMenu->registerChoiceDonePollValue(&submenuSelection);
    colorSelectionMenu->registerChoiceDonePollValue(&colorSelection);
    networkConnectionMenu->registerChoiceDonePollValue(&networkSelection);
}

void Settings::udpDataReceived(int messageID, std::vector<uint8_t> data) {

}

Settings::~Settings() {
    delete settingsMainMenu;
    delete colorSelectionMenu;
    delete networkConnectionMenu;
}

void Settings::checkSelections()
{
    if(submenuSelection != -1 && currentState == SETTINGS_MENU)
    {
       
        Serial.println("wrong case");
        currentState = (SettingState)(submenuSelection+1);
        if(currentState == SETTINGS_NETWORK_CONNECTION_MENU) {
            networkConnectionMenu->requestActivation();
        }
        else{
            colorSelectionMenu->requestActivation();
        }
        
        submenuSelection = -1;
        colorSelection = -1;
        networkSelection = -1;
    }

    if(colorSelection != -1 &&(currentState != SETTINGS_MENU && currentState != SETTINGS_NETWORK_CONNECTION_MENU))
    {
        switch (currentState)
        {
        case SETTINGS_SELECTION_COLOR_MENU:
            PortableOS::setSystemColor(SystemColor::SELECTION_COLOR, colorMapping[colorSelection]);
            break;
        
        case SETTINGS_BG_COLOR_MENU:
            PortableOS::setSystemColor(SystemColor::BG_COLOR, colorMapping[colorSelection]);
            break;

        case SETTINGS_MOTIVE_COLOR_MENU:
            PortableOS::setSystemColor(SystemColor::MOTIVE_COLOR, colorMapping[colorSelection]);
            break;

        default:
            break;
        }

        currentState = SETTINGS_MENU;
        colorSelection = -1;
        submenuSelection = -1;
        settingsMainMenu->requestActivation();
    }

    if(networkSelection != -1 && currentState == SETTINGS_NETWORK_CONNECTION_MENU) {
        switch(networkSelection) {
            case 0: // UPC5284544
                OS_API::connectToNetwork("monke", "banana");
            break;
            case 1: // Kuba
                OS_API::connectToNetwork("supa", "mario");
            break;
            case 2: // nie, po prostu nie
                OS_API::connectToNetwork("123", "456");
            break;
            default:
            break;
        }

        currentState = SETTINGS_MENU;
        networkSelection = -1;
        submenuSelection = -1;
        settingsMainMenu->requestActivation();
    }
}

void Settings::start(int w, int h){ 
    if(settingsMainMenu != nullptr)
    {
        settingsMainMenu->requestActivation();
    }
}

void Settings::input(InputType input){ 
    if(currentState == SETTINGS_MENU)
    {
        if(settingsMainMenu != nullptr)
        {
            settingsMainMenu->input(input);
        }
    }else if (currentState == SETTINGS_NETWORK_CONNECTION_MENU) {
        networkConnectionMenu->input(input);
    }else
    {
        colorSelectionMenu->input(input);
    }

}


void Settings::longPressInput(InputType input)
{

}

void Settings::longPressRelease(InputType input)
{

}

void Settings::analogInput(int x, int y) {
    if(currentState == SETTINGS_MENU)
    {
        if(settingsMainMenu != nullptr)
        {
            settingsMainMenu->analogInput(x,y);
        }
    }else if (currentState == SETTINGS_NETWORK_CONNECTION_MENU) {
        networkConnectionMenu->analogInput(x, y);
    }else
    {
        colorSelectionMenu->analogInput(x, y);
    }
}

void Settings::touchInput(int x, int y) {

}

void Settings::update(){
    checkSelections();
}

void Settings::render(DisplayProvider& display){
    if(currentState == SETTINGS_MENU)
    {
        if(settingsMainMenu != nullptr)
        {
            settingsMainMenu->render(display);
        }
    }else if(currentState == SETTINGS_NETWORK_CONNECTION_MENU) {
        networkConnectionMenu->render(display);
    }else
    {
        colorSelectionMenu->render(display);
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
