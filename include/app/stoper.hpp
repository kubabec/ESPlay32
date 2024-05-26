#ifndef STOPER_H
#define STOPER_H
#include "app/runtimeApplication.hpp"

class Stoper : public RuntimeApplication {
    public:
    
    Stoper();
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
    private:

    bool isDispColor = false;
    bool isPaused = false;
    int millisec = 0;
    int sec = 0;
    int min = 0;
    int hour = 0;
    int thousandHour = 0;
    String currentTime = "";
    int width = 0;
    int height = 0;
    unsigned long long lastUpdate = 0;

    void reset();

};

#endif