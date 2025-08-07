#ifndef RUNTIMEAPPLICATION_H
#define RUNTIMEAPPLICATION_H
#define NUMBER_OF_APPS 1
#include "targetDatatypes.hpp"
#include "os/displayprovider.hpp"
#include "app/osapi.hpp"
#include <vector>

class TFT_eSPI;

typedef enum {
    SETTINGS,
    MARCINPAINT,
    LED_COMMUNICATION,
    STOPER,
    FIGHT_GAME,
    PONG,
    CONNECT_4,
//UPDATE_LOGS,
    MARCINAPP,
    SOME_OTHER_APP,
//    MENU_TEST_APP,
    UDP_SEND_TEST_APP,
//    TOUCH_TEST_APP,
    NONE
}RuntimeApplications;

typedef enum {
    BUTTON_A,
    BUTTON_B,
    BUTTON_C,
    BUTTON_D,
    BUTTON_E,
    BUTTON_F,
    BUTTON_K,
    BUTTON_X,
    BUTTON_Y
}InputType;

class RuntimeApplication {
    public:
    virtual void start(int w, int h) = 0;
    virtual void input(InputType input) = 0;
    virtual void longPressInput(InputType input) = 0;
    virtual void longPressRelease(InputType input) = 0;
    virtual void analogInput(int x, int y) = 0;
    virtual void touchInput(int x, int y) = 0;
    virtual void update() = 0;
    virtual void render(DisplayProvider& display) = 0;
    virtual void forceRender(DisplayProvider& display) = 0;
    virtual void end() = 0;
    virtual String getAppNameString() = 0;
    virtual uint16_t getBackgroundColor() = 0;
    virtual void udpDataReceived(int messageID, std::vector<uint8_t> data) = 0;
};

#endif
