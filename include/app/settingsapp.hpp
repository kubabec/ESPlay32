#ifndef SETTINGS_H
#define SETTINGS_H
#include <app/runtimeApplication.hpp>
#include <os/menu.hpp>


class Settings : public RuntimeApplication
{
    enum SettingState
    {
        SETTINGS_MENU,
        SETTINGS_SELECTION_COLOR_MENU,
        SETTINGS_BG_COLOR_MENU,
        SETTINGS_MOTIVE_COLOR_MENU
    };

    SettingState currentState = SETTINGS_MENU;

    Menu* settingsMainMenu = nullptr;
    Menu* colorSelectionMenu = nullptr;

    int8_t submenuSelection = -1;
    int8_t colorSelection = -1;

    void checkSelections();

    public:
    Settings();
    ~Settings();
    virtual void start(int w, int h) override;
    virtual void input(InputType input) override;
    virtual void longPressInput(InputType input) override;
    virtual void longPressRelease(InputType input) override;
    virtual void analogInput(int x, int y) override;
    virtual void touchInput(int x, int y) override;
    virtual void update() override;
    virtual void render(DisplayProvider& display) override;
    virtual void end() override;
    virtual String getAppNameString() override;
    virtual uint16_t getBackgroundColor() override;
    void udpDataReceived(std::vector<uint8_t> data);
};


#endif