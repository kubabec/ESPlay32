#ifndef WIFI_LIST_CONNECTOR_H
#define WIFI_LIST_CONNECTOR_H
#include "app/runtimeApplication.hpp"
#include "os/menu.hpp"

class WiFiListConnector : public RuntimeApplication
{

    Menu* networkConnectionMenu = nullptr;
    int8_t networkSelection = -1;

    bool isLoaded = false;
    bool connectionRequested = false;
    public:
    WiFiListConnector();
    ~WiFiListConnector();
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
};


#endif