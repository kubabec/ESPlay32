#ifndef LED_COMMUNICATOR_H
#define LED_COMMUNICATOR_H
#include <app/runtimeApplication.hpp>
#include <app/tools/boolbutton.hpp>
#include <app/tools/slider.hpp>

class LedCommunicator : public RuntimeApplication {
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
    virtual void end() override;
    virtual String getAppNameString() override;
    virtual uint16_t getBackgroundColor() override;
    void udpDataReceived(int messageID, std::vector<uint8_t> data);
    void callback(bool isOn);
    void sliderCallback(int value);
    private:
    BoolButton testButton;
    Slider testSlider;
    bool callbackTest = false;
    bool callbackTestTwo = false;
};

#endif