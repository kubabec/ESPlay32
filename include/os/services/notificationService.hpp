#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include "app/runtimeApplication.hpp"
#include <queue>
#include "os/api/osServiceApi.hpp"

class NotificationService : public RuntimeApplication{
    std::queue<Notification> pendingNotifications;
    Notification currentDisplayedNotification;
    bool contextTakenOver = false;

    // Draw helpers
    bool isVerticalRolloutCompleted = false;
    bool isRolloutStarted = false;
    bool isRolloutCompleted = false;

    const int notificationTopPadding = 50; // px
    const int notificationHeight = 200; // px
    const int notificationWidthIncreaseFactor = 5; // px
    int notificationSidePadding = 30;
    int notificationCurrentX = notificationSidePadding;
    int notificationCurrentY = notificationTopPadding;

public:
    NotificationService();
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

    void pushNotification(Notification& notif);
};

#endif