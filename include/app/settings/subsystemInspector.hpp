#ifndef SUBSYSTEM_INSPECTOR_H
#define SUBSYSTEM_INSPECTOR_H
#include "app/runtimeApplication.hpp"

class SubsystemInspector : public RuntimeApplication
{

    SubsystemOverview currentOverview;
    bool isNewOverviewReceived = true;

    void readSubsystemData();
    public:
    SubsystemInspector();
    ~SubsystemInspector();
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