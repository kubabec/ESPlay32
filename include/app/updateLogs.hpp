#ifndef UPDATELOGS_H
#define UPDATELOGS_H
#include "app/runtimeApplication.hpp"

class UpdateLogs : public RuntimeApplication {
    String logs[10] = {"02.06.2024 - new update logs added", "2009: A Silly Odyssey", "shreck is cool", "placeholdear_lol", "[SUCCESS] Took 33.37 seconds", "chyba tak, nie?", "hhhHHhhHhHhh", "bez polskich znackow", "CORRUPTION%", "text"};
    int firstChosenUpdate = 0;
    bool refreshNeeded = false;
    public:
    
    UpdateLogs();
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
};

#endif