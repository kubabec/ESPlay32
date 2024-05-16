#ifndef SUBSYSTEM_MONITOR_H
#define SUBSYSTEM_MONITOR_H

#include "app/runtimeApplication.hpp"
#include "os/osDatatypes.hpp"



class SubsystemMonitorService : RuntimeApplication
{
    const uint8_t numberOfTicksToDisconnect = 50;
    uint8_t currentTickValue = 0;

    SubsystemOverview* subsystemOverviewPtr;
    public:
    SubsystemMonitorService(SubsystemOverview* subsystemOverview);
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
    virtual void udpDataReceived(int messageID, std::vector<uint8_t> data) override;

    void subsystemStatusReceived();

};

#endif