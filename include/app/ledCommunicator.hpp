#ifndef LED_COMMUNICATOR_H
#define LED_COMMUNICATOR_H
#include "app/runtimeApplication.hpp"
#include "app/tools/boolbutton.hpp"
#include "app/tools/slider.hpp"

typedef struct {
    uint8_t r, g, b;
}LedColor;

typedef struct {
    uint8_t brightness = 100;
    LedColor ledZero;
    LedColor ledOne;
}LedMessageContent;

class LedCommunicator : public RuntimeApplication {
    std::vector<Slider*> touchSliders;
    public:

    
    LedCommunicator();
    virtual void start(int w, int h) override;
    virtual void input(InputType input) override;
    virtual void longPressInput(InputType input) override;
    virtual void longPressRelease(InputType input) override;
    virtual void analogInput(int x, int y) override;
    virtual void touchInput(int x, int y) override;
    virtual void update() override;
    virtual void render(DisplayProvider& display) override;
    virtual void forceRender(DisplayProvider& display) override;
    virtual void end() override;
    virtual String getAppNameString() override;
    virtual uint16_t getBackgroundColor() override;
    void udpDataReceived(int messageID, std::vector<uint8_t> data);
    void updateLedShieldData(LedMessageContent& msg);
    void callback(int buttonId, bool isOn);
    void sliderCallback(int sliderId, int value);
    private:
    bool isRenderNeeded = true;
    BoolButton buttonEn1, buttonEn2;
    Slider slider1, slider2, slider3, slider4, slider5, slider6, brightnessSlider;
    LedMessageContent messageContent;

    bool isOneOff = true, isSndOff = true;
};

#endif