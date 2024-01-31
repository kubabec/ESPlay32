#include <app/settingsapp.hpp>
#include <os/portableos.hpp>

std::vector<String> menuOptions = {"Kolor zaznaczenia", "Kolor tla", "Kolor motywu"};
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
    colorSelectionMenu = new Menu(colors);

    settingsMainMenu->registerChoiceDonePollValue(&submenuSelection);
    colorSelectionMenu->registerChoiceDonePollValue(&colorSelection);
}

Settings::~Settings() {
    delete settingsMainMenu;
    delete colorSelectionMenu;
}

void Settings::checkSelections()
{
    if(submenuSelection != -1 && currentState == SETTINGS_MENU)
    {
       
        Serial.println("wrong case");
        currentState = (SettingState)(submenuSelection+1);
        colorSelectionMenu->requestActivation();
        submenuSelection = -1;
        colorSelection = -1;
    }

    if(colorSelection != -1 && currentState != SETTINGS_MENU)
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
