#ifndef HUMAN_RUN_H
#define HUMAN_RUN_H

#include "app/runtimeApplication.hpp"

class HumanRun : public RuntimeApplication
{
public:
    HumanRun();
    ~HumanRun();
    void start(int w, int h);
    void input(InputType input);
    void longPressInput(InputType input);
    void longPressRelease(InputType input);
    void analogInput(int x, int y);
    void touchInput(int x, int y);
    void update();
    void render(DisplayProvider &display);
    void forceRender(DisplayProvider &display);
    void end();
    void udpDataReceived(int messageID, std::vector<uint8_t> data);
    String getAppNameString();
    uint16_t getBackgroundColor();
};

#endif // PONG_H
