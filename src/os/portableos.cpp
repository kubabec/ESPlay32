#include <os/portableos.hpp>


std::vector<String> appNames = {"Stoper", "Fight Game", "Pong", "Connect 4", "Color Picker", "UDP test app", "Ustawienia"};

// Create static objects instances
DisplayProvider PortableOS::display = DisplayProvider();
Menu PortableOS::mainMenu = Menu(appNames);
bool PortableOS::isMainMenuActive = true;
RuntimeApplication* PortableOS::currentRunningAppPtr = nullptr;
TopOverlay PortableOS::topOverlay = TopOverlay();
int PortableOS::fpsCounter = 0;
uint8_t PortableOS::appTextTimeout = 0;
long PortableOS::appTextTimeoutMs = 0;
uint32_t PortableOS::systemColors[3] = {TFT_GREENYELLOW, TFT_BLACK, 0x00ED75};

void PortableOS::init(){
#ifdef EMULATOR
    display.generateScene();
#else
        TouchInputDriver::setTftAccess(display.tftDirectAccess());
#endif

    // Register callback to let Menu object run any application in the future
    mainMenu.registerChoiceDoneCallback(&mainMenuChoice);


    MainLoadingScreen::init();
    display.fillScreen(160040);
    while(!MainLoadingScreen::update())
    {
        MainLoadingScreen::render(display);
        delay(5);
    }
    delay(300);
    display.fillScreen(TFT_BLACK);
}

void PortableOS::osTask10ms()
{
    // Depending if Menu is active
    if (isMainMenuActive) {
        // Render Menu
        if(topOverlay.isHidingAnimationPending())
        {
            mainMenu.forceRefresh();
        }
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

    // Count FPS
    fpsCounter++;
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

void PortableOS::longPressInput(InputType input)
{
    if(currentRunningAppPtr != nullptr){
        currentRunningAppPtr->longPressInput(input);
    }
}

void PortableOS::longPressRelease(InputType input)
{
    if(currentRunningAppPtr != nullptr){
        currentRunningAppPtr->longPressRelease(input);
    }
}

void PortableOS::analogInput(int x, int y) {
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


void PortableOS::touchInput(int x, int y)
{
    if(currentRunningAppPtr != nullptr){
        currentRunningAppPtr->touchInput(x, y - topOverlay.getHeight());
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
}

bool PortableOS::sendUDP(MessageUDP& data)
{
    MessageUART transmisionMsg(UDP_OUTGOING_PACKAGE);
    while(data.switchToNextByte())
    {
        transmisionMsg.pushData(data.getCurrentByte());
    }
    UARTCommunicator::transmit(transmisionMsg);

    return true;
}
 