#include "os/portableOs.hpp"

std::vector<String> appNames = {"Ustawienia", "Led communicator", "Stoper", "Fight Game", "Pong", "Connect 4", "Color Picker", "Human Run"};

// Create static objects instances
DisplayProvider PortableOS::display = DisplayProvider();
Menu PortableOS::mainMenu = Menu(appNames);
bool PortableOS::isMainMenuActive = true;
bool PortableOS::isContextTakenOverMode = false;
RuntimeApplication *PortableOS::contextOvertaker = nullptr;
RuntimeApplication *PortableOS::currentRunningAppPtr = nullptr;
TopOverlay PortableOS::topOverlay = TopOverlay();
int PortableOS::fpsCounter = 0;
uint8_t PortableOS::appTextTimeout = 0;
long PortableOS::appTextTimeoutMs = 0;
uint32_t PortableOS::systemColors[3] = {TFT_GREENYELLOW, TFT_BLACK, TFT_SKYBLUE};
bool PortableOS::wasNetworkConnectedNotificationShowed = false;
// SubsystemStatusData PortableOS::currentSubsystemStatus = {
//     .isWiFiConnectedFlag = false,
//     .wasWiFiRequestedFlag = false
// };
// NetworkCredentials PortableOS::currentConnectedNetworkCredentials;

// .isCommunicating = false,
// .data = {
//     .isWiFiConnectedFlag = false,
//     .isWiFiRequestedFlag = false,
//     .ipOctet1 = 0,
//     .ipOctet2 = 0,
//     .ipOctet3 = 0,
//     .ipOctet4 = 0
// },
// .credentials =
// {
//     .ssid = "none",
//     .password = "none"
// }

NotificationService PortableOS::notificationService;

void PortableOS::init()
{
#ifdef EMULATOR
    display.generateScene();
#else
    TouchInputDriver::setTftAccess(display.tftDirectAccess());
#endif

    // Register callback to let Menu object run any application in the future
    mainMenu.registerChoiceDoneCallback(&mainMenuChoice);

    // MainLoadingScreen::init();
    // display.fillScreen(160040);
    // while(!MainLoadingScreen::update())
    // {
    //     MainLoadingScreen::render(display);
    //     delay(5);
    // }
    // delay(200);
    display.fillScreen(TFT_BLACK);

    /*Test of BITMAP PRINTING */

    /*Test of BITMAP PRINTING */
}

void PortableOS::osTaskUnlimited()
{
    if (!isContextTakenOverMode)
    {
        // Depending if Menu is active
        if (!isMainMenuActive)
        {
            // Otherwise render and update currently running application
            // currentRunningAppPtr->update();
            currentRunningAppPtr->render(display);
        }

        display.setOverlayMode(true);
        topOverlay.render(display);
        display.setOverlayMode(false);
    }
    else
    {
        if (contextOvertaker != nullptr)
        {
            display.setOverlayMode(true);
            contextOvertaker->render(display);
            display.setOverlayMode(false);
        }
    }
}

void PortableOS::osTask10ms()
{
    internalServicesTask();

    if (!isContextTakenOverMode)
    {
        // Depending if Menu is active
        if (isMainMenuActive)
        {
            // Render Menu
            if (topOverlay.isHidingAnimationPending())
            {
                mainMenu.forceRefresh();
            }
            mainMenu.update();
            mainMenu.render(display);
        }
        else
        {
            // Otherwise render and update currently running application
            currentRunningAppPtr->update();
            // currentRunningAppPtr->render(display);
        }

        // display.setOverlayMode(true);
        // topOverlay.render(display);
        // display.setOverlayMode(false);
    }
    // else
    // {
    //     if (contextOvertaker != nullptr)
    //     {
    //         display.setOverlayMode(true);
    //         contextOvertaker->render(display);
    //         display.setOverlayMode(false);
    //     }
    // }

    // Count FPS
    fpsCounter++;
}

void PortableOS::internalServicesTask()
{
    notificationService.update();
}

void PortableOS::osTask1s()
{
    // Display FPS counter every 1s
    // display.setOverlayMode(true);
    // display.setTextSize(1);
    // display.setTextFont(2);
    // display.setTextColor(TFT_WHITE,TFT_DARKGREEN);
    // display.drawString("FPS : " + String(fpsCounter) + "  ", 400, 15);
    // display.setOverlayMode(false);

    fpsCounter = 0;
}

void PortableOS::input(InputType systemInput)
{
    if (!isContextTakenOverMode)
    {
        // Exception for killing app
        if (systemInput == BUTTON_F)
        {
            // We got app running (no menu active and ptr is not nullptr)
            if (!isMainMenuActive && (currentRunningAppPtr != nullptr) && !topOverlay.isActivationAnimation())
            {
                // Request app finish
                currentRunningAppPtr->end();

                // Set Menu display area
                display.setAppDisplayArea({0, 0, 480, 320});
                display.setTextColor(TFT_WHITE, TFT_BLACK);
                // // Request menu to get activated
                mainMenu.requestActivation();
                isMainMenuActive = true;
                // Release app memory
                delete currentRunningAppPtr;
                currentRunningAppPtr = nullptr;
                topOverlay.deactivate();
                appTextTimeout = 0;

                if (TouchInputDriver::isTouchEnabled())
                {
                    TouchInputDriver::disableTouch();
                }
            }
        }
        else
        {
            // Forward input to Menu or App depending on what is active
            if (isMainMenuActive)
            {
                if (!topOverlay.isHidingAnimationPending())
                {
                    mainMenu.input(systemInput);
                }
            }
            else
            {
                currentRunningAppPtr->input(systemInput);
            }
        }
    }
    else
    {
        if (contextOvertaker != nullptr)
        {
            contextOvertaker->input(systemInput);
        }
    }
}

void PortableOS::longPressInput(InputType input)
{
    if (currentRunningAppPtr != nullptr)
    {
        currentRunningAppPtr->longPressInput(input);
    }
}

void PortableOS::longPressRelease(InputType input)
{
    if (currentRunningAppPtr != nullptr)
    {
        currentRunningAppPtr->longPressRelease(input);
    }
}

void PortableOS::analogInput(int x, int y)
{
    if (isMainMenuActive)
    {
        if (!topOverlay.isHidingAnimationPending())
        {
            mainMenu.analogInput(x, y);
        }
    }
    else
    {
        if (currentRunningAppPtr != nullptr)
        {
            currentRunningAppPtr->analogInput(x, y);
        }
    }
}

void PortableOS::touchInput(int x, int y)
{
    if (!isContextTakenOverMode)
    {
        if (currentRunningAppPtr != nullptr)
        {
            currentRunningAppPtr->touchInput(x, y - topOverlay.getHeight());
        }
    }
    else
    {
        if (contextOvertaker != nullptr)
        {
            contextOvertaker->touchInput(x, y);
        }
    }
}

void PortableOS::mainMenuChoice(int8_t choice)
{
    // We received correct request
    if (choice != -1)
    {
        AppDisplayArea newDisplayArea;
        switch (choice)
        {
        // Run requested application
        case STOPER:
            currentRunningAppPtr = new Stoper();
            newDisplayArea = {0, topOverlay.getHeight(), 480, (uint16_t)(320 - topOverlay.getHeight())};
            break;
        case FIGHT_GAME:
            currentRunningAppPtr = new FightGame();
            newDisplayArea = {0, topOverlay.getHeight(), 480, (uint16_t)(320 - topOverlay.getHeight())};
            break;
        case PONG:
            currentRunningAppPtr = new PongLauncher();
            newDisplayArea = {0, topOverlay.getHeight(), 480, (uint16_t)(320 - topOverlay.getHeight())};
            break;
        case CONNECT_4:
            TouchInputDriver::enableTouch();
            currentRunningAppPtr = new Connect4();
            newDisplayArea = {0, topOverlay.getHeight(), 480, (uint16_t)(320 - topOverlay.getHeight())};
            break;
            // case UPDATE_LOGS:
            //     currentRunningAppPtr = new UpdateLogs();
            //     newDisplayArea = {0, topOverlay.getHeight(), 480, (uint16_t)(320 - topOverlay.getHeight())};
            //     break;
        case HUMAN_RUN:
            currentRunningAppPtr = new HumanRun();
            newDisplayArea = {0, topOverlay.getHeight(), 480, (uint16_t)(320 - topOverlay.getHeight())};
            break;
        case LED_COMMUNICATION:
            TouchInputDriver::enableTouch();
            currentRunningAppPtr = new LedCommunicator();
            newDisplayArea = {0, topOverlay.getHeight(), 480, (uint16_t)(320 - topOverlay.getHeight())};
            break;
        case SOME_OTHER_APP: // color picker
            currentRunningAppPtr = new SomeOtherApp();
            newDisplayArea = {0, topOverlay.getHeight(), 480, (uint16_t)(320 - topOverlay.getHeight())};
            break;
        // case UDP_SEND_TEST_APP:
        //     // TouchInputDriver::enableTouch();
        //     currentRunningAppPtr = new UDPSendTestApp();
        //     newDisplayArea = {0, topOverlay.getHeight(), 480, (uint16_t)(320 - topOverlay.getHeight())};
        //     break;
        case SETTINGS:
            currentRunningAppPtr = new Settings();
            newDisplayArea = {0, topOverlay.getHeight(), 480, (uint16_t)(320 - topOverlay.getHeight())};
            break;

        default:
            break;
        }

        // Check if application is correctly created
        if (currentRunningAppPtr != nullptr)
        {
            display.setAppDisplayArea(newDisplayArea);
            // Request app start up
            currentRunningAppPtr->start(newDisplayArea.w, newDisplayArea.h);
            topOverlay.setOverlayText(currentRunningAppPtr->getAppNameString());
            topOverlay.activate();
            display.fillScreen(currentRunningAppPtr->getBackgroundColor());
            isMainMenuActive = false;
        }
        else
        {
            // Otherwise, request Menu to gets active again
            mainMenu.requestActivation();

            isMainMenuActive = true;
        }
    }
}

uint32_t PortableOS::getSystemColor(SystemColor col)
{
    switch (col)
    {
    case SELECTION_COLOR:
        return systemColors[0];
    case BG_COLOR:
        return systemColors[1];
    case MOTIVE_COLOR:
        return systemColors[2];

    default:
        return 0;
    }
}

void PortableOS::setSystemColor(SystemColor col, uint32_t value)
{
    switch (col)
    {
    case SELECTION_COLOR:
        systemColors[SELECTION_COLOR] = value;
        break;
    case BG_COLOR:
        systemColors[BG_COLOR] = value;
        break;
    case MOTIVE_COLOR:
        systemColors[MOTIVE_COLOR] = value;
        break;

    default:
        break;
    }
}

bool PortableOS::activateAppTextMode(String appText, uint32_t textColor, uint8_t timeout)
{
    PortableOS::appTextTimeout = timeout;
#ifndef EMULATOR
    PortableOS::appTextTimeoutMs = millis();
#endif

    return PortableOS::topOverlay.activateAppTextMode(appText, textColor);
}

bool PortableOS::deactivateAppTextMode()
{
    return PortableOS::topOverlay.deactivateAppTextMode();
}

bool PortableOS::sendUDP(MessageUDP &data)
{
    // TODO
    return true;
}

bool PortableOS::sendBroadcast(MessageUDP &data)
{
    // MessageUDP::IPAddr ipRef = data.getIPAddress();

    // ipRef.element1 = subsystemOverview.data.ipOctet1;
    // ipRef.element2 = subsystemOverview.data.ipOctet2;
    // ipRef.element3 = subsystemOverview.data.ipOctet3;

    // // Workaround for Iphone network
    // if (subsystemOverview.data.ipOctet1 != 172)
    // {
    //     ipRef.element4 = 255;
    // }
    // else
    // {
    //     ipRef.element4 = 15;
    // }

    // data.setIpAddress(ipRef);
    // PortableOS::sendUDP(data);

    return true;
}

void PortableOS::connectToNetwork(std::string ssid, std::string password)
{
    // TODO
}

void PortableOS::disconnectWiFiNetwork()
{
    // TODO

    // Notification networkDisconnected{
    //     .title = "Network disconnected",
    //     .text = "WiFi network has been disconnected.",
    //     .bgcolor = TFT_LIGHTGREY
    // };
    // OS_API::pushNotification(networkDisconnected);

    // wasNetworkConnectedNotificationShowed = false;
}

void PortableOS::pushNotification(Notification &notif)
{
    notificationService.pushNotification(notif);
}

bool PortableOS::contextOvertake(RuntimeApplication *overtaker)
{
    if (overtaker != nullptr)
    {
        contextOvertaker = overtaker;
        isContextTakenOverMode = true;

        Serial.println("Context Overtaken");
        return true;
    }

    return false;
}

void PortableOS::contextRelease()
{
    isContextTakenOverMode = false;
    contextOvertaker = nullptr;

    if (isMainMenuActive)
    {
        mainMenu.forceRender(display);
    }
    else
    {
        topOverlay.forceRender(display);
        if (currentRunningAppPtr != nullptr)
        {
            currentRunningAppPtr->forceRender(display);
        }
    }
}
