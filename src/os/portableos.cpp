#include "os/portableOs.hpp"


std::vector<String> appNames = {"Ustawienia", "Led communicator", "Stoper", "Fight Game", "Pong", "Connect 4", "Update Logs", "Color Picker", "UDP test app"};

// Create static objects instances
DisplayProvider PortableOS::display = DisplayProvider();
Menu PortableOS::mainMenu = Menu(appNames);
bool PortableOS::isMainMenuActive = true;
RuntimeApplication* PortableOS::currentRunningAppPtr = nullptr;
TopOverlay PortableOS::topOverlay = TopOverlay();
int PortableOS::fpsCounter = 0;
uint8_t PortableOS::appTextTimeout = 0;
long PortableOS::appTextTimeoutMs = 0;
uint32_t PortableOS::systemColors[3] = {TFT_GREENYELLOW, TFT_BLACK, TFT_SKYBLUE};
// SubsystemStatusData PortableOS::currentSubsystemStatus = {
//     .isWiFiConnectedFlag = false,
//     .wasWiFiRequestedFlag = false
// };
// NetworkCredentials PortableOS::currentConnectedNetworkCredentials;
// bool PortableOS::isSubsystemComunicating = false;
SubsystemOverview PortableOS::subsystemOverview;
    //.isCommunicating = false
    // .data = { 
    //     .isWiFiConnectedFlag = false, 
    //     .isWiFiRequestedFlag = false
    // },
    // .credentials = { 
    //     .ssid = "none",
    //     .password = "none"
    // }
SubsystemMonitorService PortableOS::subsystemMonitor(&subsystemOverview);
NotificationService PortableOS::notificationService;
std::vector<Services*> PortableOS::services; 

void PortableOS::init(){
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
    // delay(300);
    display.fillScreen(TFT_BLACK);

    services.push_back(&notificationService);
}

void PortableOS::osTask10ms()
{
    internalServicesTask();

    if (!notificationService.isContextTakenOver()) {
            // Depending if Menu is active
        if (isMainMenuActive) {
            // Render Menu
            if(topOverlay.isHidingAnimationPending())
            {
                mainMenu.forceRefresh();
            }
            mainMenu.update();
            mainMenu.render(display);
        }
        else {
            // Otherwise render and update currently running application
            currentRunningAppPtr->update();
            currentRunningAppPtr->render(display);

    #ifndef EMULATOR
            // Timeouted deactivation of App overlay text
            if(appTextTimeout > 0)
            {     
                if(millis() - appTextTimeoutMs > 1000)
                {
                    appTextTimeout --;
                    appTextTimeoutMs = millis();

                    if(appTextTimeout == 0)
                    {
                        topOverlay.deactivateAppTextMode();
                    }
                }

            }
    #endif
        }

        display.setOverlayMode(true);
        topOverlay.render(display);
        display.setOverlayMode(false);
    }
    else {
        notificationService.render();
    }

    // Count FPS
    fpsCounter++;
}

void PortableOS::internalServicesTask()
{
    subsystemMonitor.update();
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
    if (!notificationService.isContextTakenOver()) {
        // Exception for killing app
        if(systemInput == BUTTON_F){
            // We got app running (no menu active and ptr is not nullptr)
            if(!isMainMenuActive && (currentRunningAppPtr != nullptr) && !topOverlay.isActivationAnimation())
            {
                // Request app finish
                currentRunningAppPtr->end();

                // Set Menu display area
                display.setAppDisplayArea({0,0,480,320});
                display.setTextColor(TFT_WHITE, TFT_BLACK);
                // // Request menu to get activated
                mainMenu.requestActivation();
                isMainMenuActive = true;
                // Release app memory
                delete currentRunningAppPtr;
                currentRunningAppPtr = nullptr;
                topOverlay.deactivate();
                appTextTimeout = 0;

                if(TouchInputDriver::isTouchEnabled())
                {
                    TouchInputDriver::disableTouch();
                }
            }
        }else {
            // Forward input to Menu or App depending on what is active
            if (isMainMenuActive){
                if (!topOverlay.isHidingAnimationPending()) {
                    mainMenu.input(systemInput);
                }

            }else {
                currentRunningAppPtr->input(systemInput);
            }
        }
    }
    else {
        notificationService.input(systemInput);
    }
}

void PortableOS::longPressInput(InputType input)
{
    if (!notificationService.isContextTakenOver()) {
        if(currentRunningAppPtr != nullptr){
            currentRunningAppPtr->longPressInput(input);
        }
    }
}

void PortableOS::longPressRelease(InputType input)
{
    if (!notificationService.isContextTakenOver()) {
        if(currentRunningAppPtr != nullptr){
            currentRunningAppPtr->longPressRelease(input);
        }
    }
}

void PortableOS::analogInput(int x, int y) {
    if (!notificationService.isContextTakenOver()) {
        if (isMainMenuActive){
            if (!topOverlay.isHidingAnimationPending()) {
                mainMenu.analogInput(x, y);
            }

            }
        else {
            if(currentRunningAppPtr != nullptr){
                currentRunningAppPtr->analogInput(x, y);
            }
        }
    }
}


void PortableOS::touchInput(int x, int y)
{
    if (!notificationService.isContextTakenOver()) {
        if(currentRunningAppPtr != nullptr){
            currentRunningAppPtr->touchInput(x, y - topOverlay.getHeight());
        }
    }
}

void PortableOS::mainMenuChoice(int8_t choice)
{
    // We received correct request
    if(choice != -1){
        AppDisplayArea newDisplayArea;
        switch(choice)
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
            case UPDATE_LOGS:
                currentRunningAppPtr = new UpdateLogs();
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
            case UDP_SEND_TEST_APP:
                // TouchInputDriver::enableTouch();
                currentRunningAppPtr = new UDPSendTestApp();
                newDisplayArea = {0, topOverlay.getHeight(), 480, (uint16_t)(320 - topOverlay.getHeight())};
                break;
            case SETTINGS:
                currentRunningAppPtr = new Settings();
                newDisplayArea = {0, topOverlay.getHeight(), 480, (uint16_t)(320 - topOverlay.getHeight())};
                break;
            
            default:
                break;
        }


        // Check if application is correctly created
        if(currentRunningAppPtr != nullptr){
            display.setAppDisplayArea(newDisplayArea);
            // Request app start up
            currentRunningAppPtr->start(newDisplayArea.w, newDisplayArea.h);
            topOverlay.setOverlayText(currentRunningAppPtr->getAppNameString());
            topOverlay.activate();
            display.fillScreen(currentRunningAppPtr->getBackgroundColor());
            isMainMenuActive = false;
        }else
        {
            // Otherwise, request Menu to gets active again
            mainMenu.requestActivation();

            isMainMenuActive = true;
        }
    }
}


uint32_t PortableOS::getSystemColor(SystemColor col)
{
    switch(col)
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
    switch(col)
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

void PortableOS::udpMessageRecieved(MessageUDP& msg) {
    if (currentRunningAppPtr != nullptr) {
        currentRunningAppPtr->udpDataReceived(msg.getId(), msg.getPayload());
    }

    // Notify subsystemMonitor that slave is communicating
    subsystemMonitor.subsystemStatusReceived();
}

void PortableOS::subsystemStatusReceived(SubsystemStatusData& data)
{
    memcpy(&subsystemOverview.data, &data, sizeof(data));
    subsystemOverview.isCommunicating = true;

    // Notify subsystemMonitor that slave is communicating
    subsystemMonitor.subsystemStatusReceived();

    Serial.println(String(subsystemOverview.data.ipOctet1) + "." + String(subsystemOverview.data.ipOctet2) + "." + String(subsystemOverview.data.ipOctet3) + "." + String(subsystemOverview.data.ipOctet4));

    //Serial.print("=");
}

void PortableOS::networkSsidReceived(String& ssid)
{
    //currentConnectedNetworkCredentials.ssid = ssid;
    subsystemOverview.credentials.ssid = ssid;

    // Notify subsystemMonitor that slave is communicating
    subsystemMonitor.subsystemStatusReceived();
}

void PortableOS::networkPasswordReceived(String& password)
{
    //currentConnectedNetworkCredentials.password = password;
    subsystemOverview.credentials.password = password;

    // Notify subsystemMonitor that slave is communicating
    subsystemMonitor.subsystemStatusReceived();
}

void PortableOS::networkDataReceived(NetworkDataUARTMessage& data)
{
    StringBuffer ssid(data.ssid);
    String ssidString = ssid.toString();
    StringBuffer password(data.password);
    String passwordString = password.toString();

    //Serial.println("Received network Data : " + ssidString + " , " + passwordString);

    subsystemOverview.credentials.ssid = ssidString;
    subsystemOverview.credentials.password = passwordString;
}



bool PortableOS::sendUDP(MessageUDP& data)
{
    MessageUART transmissionMsg(UDP_OUTGOING_PACKAGE);
    data.resetByteIterationCount();
    while(data.switchToNextByte())
    {
        transmissionMsg.pushData(data.getCurrentByte());
    }
    UARTCommunicator::transmit(transmissionMsg);

    return true;
}

bool PortableOS::sendBroadcast(MessageUDP& data)
{
    MessageUDP::IPAddr ipRef = data.getIPAddress();

    ipRef.element1 = subsystemOverview.data.ipOctet1;
    ipRef.element2 = subsystemOverview.data.ipOctet2;
    ipRef.element3 = subsystemOverview.data.ipOctet3;

    // Workaround for Iphone network
    if(subsystemOverview.data.ipOctet1 != 172){
        ipRef.element4 = 255;
    }
    else 
    {
        ipRef.element4 = 15;
    }
    
    data.setIpAddress(ipRef);
    PortableOS::sendUDP(data);

    return true;
}

void PortableOS::connectToNetwork(std::string ssid, std::string password) {
    MessageUART transmissionSsid(CONNECT_TO_NETWORK_SSID);
    MessageUART transmissionPassword(CONNECT_TO_NETWORK_PASSWORD);

    String ssidStringTmp(ssid.c_str());
    String pwdStringTmp(password.c_str());

    StringBuffer ssidTmp(ssidStringTmp);
    StringBuffer passwordTmp(pwdStringTmp);

    transmissionSsid.pushData((uint8_t*)ssidTmp.getBuffer(), 40);
    transmissionPassword.pushData((uint8_t*)passwordTmp.getBuffer(), 40);

    UARTCommunicator::transmit(transmissionSsid);
    delay(5);
    UARTCommunicator::transmit(transmissionPassword);
}

void PortableOS::disconnectWiFiNetwork()
{
    MessageUART disconnectRequest(NETWORK_DISCONNECT_REQUEST);
    UARTCommunicator::transmit(disconnectRequest);
}
 

const SubsystemOverview PortableOS::getSubsystemOverview()
{
    // SubsystemOverview retVal;
    // retVal.data = currentSubsystemStatus;
    // retVal.isCommunicating = isSubsystemComunicating;
    // retVal.credentials = currentConnectedNetworkCredentials;

    return subsystemOverview;
}

void PortableOS::pushNotification(Notification& notif) {
    notificationService.pushNotification(notif);
}
