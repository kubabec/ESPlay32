#ifndef PORTABLEOS_H
#define PORTABLEOS_H
#include "app/runtimeApplication.hpp"
#include "os/menu.hpp"
#include "os/displayprovider.hpp"
#include "os/topoverlay.hpp"
#include "app/testApps.hpp"
#include "app/games/fightgame.hpp"
#include "app/games/pong.h"
#include "app/games/connect4.h"
#include "app/ledCommunicator.hpp"
#include "app/updateLogs.hpp"
#include "app/marcinApp.hpp"
#include "app/settings/settingsMainApp.hpp"
#include "os/drivers/touchinputdriver.hpp"
#include "networkTools/messageUDP.hpp"
#include "networkTools/uartCommunicator.hpp"
#include "os/mainloadingscreen.h"
#include "os/osDatatypes.hpp"
#include "app/marcinPaint.hpp"

// Services
#include "os/services/subsystemMonitor.hpp"
#include "os/services/notificationService.hpp"


#ifdef EMULATOR
    #include "../devicescreenemulator.h"
#endif


enum SystemColor
{
    SELECTION_COLOR,
    BG_COLOR,
    MOTIVE_COLOR
};

class PortableOS{
    // MainMenu instance
    static Menu mainMenu;
    static bool isMainMenuActive;
    static bool isContextTakenOverMode;
    static RuntimeApplication* contextOvertaker;
    static TopOverlay topOverlay;

    static uint32_t systemColors[3];

    // Pointer to currently running app (if any)
    static RuntimeApplication* currentRunningAppPtr;
    // Counter of FPS flushed
    static int fpsCounter;
    static uint8_t appTextTimeout;
    static long appTextTimeoutMs;


    // static SubsystemStatusData currentSubsystemStatus;
    // static NetworkCredentials currentConnectedNetworkCredentials;
    // static bool isSubsystemComunicating;
    static SubsystemOverview subsystemOverview;
    static bool wasNetworkConnectedNotificationShowed;


    
    public:
    // TFT display instance
    static DisplayProvider display;

    /**** SERVICES *****/
    static SubsystemMonitorService subsystemMonitor;
    static NotificationService notificationService;
    /**** SERVICES *****/

    // Main 25ms task
    static void osTask10ms();
    static void internalServicesTask();
    // 1s task
    static void osTask1s();
    // OS init function
    static void init();
    // Digital input function
    static void input(InputType systemInput);
    static void longPressInput(InputType input);
    static void longPressRelease(InputType input);

    static void analogInput(int x, int y);

    static void touchInput(int x, int y);

    // Application launcher
    static void mainMenuChoice(int8_t choice);

    static uint32_t getSystemColor(SystemColor col);
    static void setSystemColor(SystemColor col, uint32_t value);

    // On top-bar text activation
    static bool activateAppTextMode(String appText, uint32_t textColor, uint8_t timeout = 0);
    static bool deactivateAppTextMode();

    static void udpMessageRecieved(MessageUDP& msg);
    static void subsystemStatusReceived(SubsystemStatusData& data);
    static void networkSsidReceived(String& ssid);
    static void networkPasswordReceived(String& password);
    static void networkDataReceived(NetworkDataUARTMessage& data);


    // OS Service API
    static bool contextOvertake(RuntimeApplication* overtaker);
    static void contextRelease();

    // OS API TEST
    static bool sendUDP(MessageUDP& data);
    static bool sendBroadcast(MessageUDP& data);
    static void connectToNetwork(std::string ssid, std::string password);
    static void disconnectWiFiNetwork();
    static const SubsystemOverview getSubsystemOverview();
    static void pushNotification(Notification& notif);
};


#endif 
