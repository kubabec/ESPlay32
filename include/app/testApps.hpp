#ifndef TESTAPPS_H
#define TESTAPPS_H
#include "app/runtimeApplication.hpp"
#include "os/menu.hpp"


// class DummyApp : public RuntimeApplication {
//     bool needsUpdate = true;
//     public:
    
//     DummyApp(){

//     }
//     virtual void start(int w, int h) override {

//     }
//     virtual void input(InputType input) override {

//     }
//     virtual void analogInput(int x, int y) override {

//     }

//     virtual void touchInput(int x, int y) override {

//     }

//     virtual void update() override{

//     }
//     virtual void render(DisplayProvider& display) override{
//         if(needsUpdate)
//         {
//             display.fillScreen(TFT_BLUE);
//             display.setTextSize(1);
//             display.setTextColor(TFT_GREEN, TFT_BLUE);
//             //display.drawString("DummyApp", 100, 200);
//             needsUpdate = false;
//         }
//     }
//     virtual void end() override{

//     }

//     String getAppNameString() override
//     {
//         return "DummyApp";
//     }

//     uint16_t getBackgroundColor(){
//         return TFT_BLUE;
//     }
// };


class SomeOtherApp : public RuntimeApplication {
    bool needsUpdate = true;

    uint32_t currentColor = 0;
    public:
    
    SomeOtherApp(){

    }
    virtual void start(int w, int h) override {

    }
    virtual void input(InputType input) override {
        if(input == BUTTON_A)
        {
            currentColor += 100;
        }

        if(input == BUTTON_B)
        {
            currentColor += 1000;
        }

        if(input == BUTTON_C)
        {
            currentColor -= 100;
        }

        if(input == BUTTON_D)
        {
            currentColor -= 1000;
        }

        needsUpdate = true;

    }

    virtual void longPressInput(InputType input) override{}
    virtual void longPressRelease(InputType input) override{}
    void udpDataReceived(int messageID, std::vector<uint8_t> data) {}

    virtual void analogInput(int x, int y) override {
        if(y > 5)
        {
            currentColor += 10;
            needsUpdate = true;
        }

    }

    virtual void touchInput(int x, int y) override {

    }

    virtual void update() override{

    }
    virtual void render(DisplayProvider& display) override{
        if(needsUpdate)
        {
            display.fillScreen(getBackgroundColor());
            display.setTextSize(1);
            display.setTextColor(TFT_YELLOW, getBackgroundColor());
            #ifndef EMULATOR
            display.drawString("Current color value : " + String(currentColor), 30, 50);
            #else
            display.drawString("Current color value : " + QString::number(currentColor), 30, 50);
            #endif

            display.fillRect(50,100, 300, 150, currentColor);
            needsUpdate = false;
        }
    }
    virtual void end() override{

    }

    virtual String getAppNameString() override
    {
        return "ColorPicker";
    }
    uint16_t getBackgroundColor(){
        return TFT_BLACK;
    }
};


// class MenuTestApp : public RuntimeApplication {
//     bool needsUpdate = true;
//     int circleX = 0;
//     int circleY = 0;
//     int circleR = 10;

//     bool isSelectionDone = false;
//     int8_t selection = -1;

//     std::vector<String> menuOptions = {"Option 1", "Option 2", "Option 3", "Option 4", "Option 5", "Option 6"};
//     Menu* selectionMenu;
//     int8_t choicePollValue = -1;

//     void checkSelectionDone()
//     {
//         if(choicePollValue != -1)
//         {
//             isSelectionDone = true;
//             needsUpdate = true;
//             selection = choicePollValue;
//         }
//     }

//     public:
    
//     MenuTestApp(){
//         selectionMenu = new Menu(menuOptions);

//         selectionMenu->registerChoiceDonePollValue(&choicePollValue);
//     }

//     ~MenuTestApp(){
//         delete selectionMenu;
//     }
//     virtual void start(int w, int h) override {
//         selectionMenu->requestActivation();
//     }
//     virtual void input(InputType input) override {
//         if(!isSelectionDone)
//         {
//             selectionMenu->input(input);
//         }
//     }
//     virtual void analogInput(int x, int y) override {
//         if(!isSelectionDone)
//         {
//             selectionMenu->analogInput(x, y);
//         }
//     }

//     virtual void touchInput(int x, int y) override {

//     }

//     virtual void update() override{
//         if(!isSelectionDone)
//         {
//             checkSelectionDone();
//         }
//     }
//     virtual void render(DisplayProvider& display) override{
//         if(!isSelectionDone)
//         {
//             selectionMenu->render(display);
//             needsUpdate = false;
//         }

//         if(needsUpdate)
//         {
//             display.fillScreen(TFT_CYAN);
//             display.setTextSize(1);
//             display.setTextColor(TFT_BROWN, TFT_CYAN);
//             //display.drawString("Selected option : " + (String(selection+1)), 100, 200);
//             //display.fillRect(circleX, circleY, circleR+1, circleR+1, TFT_CYAN);
//             //display.fillCircle(circleX, circleY, circleR, TFT_RED);
//             needsUpdate = false;
//         }
//     }
//     virtual void end() override{

//     }

//     virtual String getAppNameString() override
//     {
//         return "Test app";
//     }

//     uint16_t getBackgroundColor(){
//         return TFT_CYAN;
//     }
// };



class TouchTestApp : public RuntimeApplication {
    bool needsUpdate = true;

    bool touchInputArrived = false;
    int input_x = 0;
    int input_y = 0;
    public:
    
    TouchTestApp(){

    }
    virtual void start(int w, int h) override {
    }
    virtual void input(InputType input) override {
    }
    virtual void longPressInput(InputType input) override{}
    virtual void longPressRelease(InputType input) override{}
    virtual void analogInput(int x, int y) override {
    }

    virtual void touchInput(int x, int y) override {
        input_x = x;
        input_y = y;
        touchInputArrived = true;
        //needsUpdate = true;
    }

    virtual void update() override{

    }
    virtual void render(DisplayProvider& display) override{
        if(needsUpdate)
        {
            display.fillScreen(getBackgroundColor());
            display.setTextSize(1);
            display.setTextColor(TFT_ORANGE, getBackgroundColor());

            display.drawString("Touch the display somewhere ", 70, 30);    

            needsUpdate = false;
        }

        if(touchInputArrived)
        {
            display.fillCircle(input_x, input_y, 5, TFT_BLACK);
            touchInputArrived = false;
        }
    }
    virtual void end() override{

    }

    void udpDataReceived(int messageID, std::vector<uint8_t> data) {}

    virtual String getAppNameString() override
    {
        return "Touch test";
    }
    uint16_t getBackgroundColor(){
        return TFT_WHITE;
    }
};


class UDPSendTestApp : public RuntimeApplication {
    bool needsUpdate = true;

    int packagesSent = 0;
    int packagesReceived = 0;
    int cyclicsToGo = 400;
    public:
    
    UDPSendTestApp(){

    }
    virtual void start(int w, int h) override {
    }
    virtual void input(InputType input) override {
    }
    virtual void longPressInput(InputType input) override{}
    virtual void longPressRelease(InputType input) override{}
    virtual void analogInput(int x, int y) override {
    }

    virtual void touchInput(int x, int y) override {

    }

    virtual void update() override{

        if(cyclicsToGo == 0)
        {
            static uint8_t keepAliveData[8] = {0};  
            MessageUDP udpKeepAliveMessage(51, (MessageUDP::IPAddr){192,168,1,255}, 9001, keepAliveData, 8);

            OS_API::sendUdpMessage(udpKeepAliveMessage);

            static bool isLevelRising = true;
            static bool isFlowRising = true;

            // Prepare UDP header + payload
            static uint8_t udpData[16] = {0};
            unsigned id = 3;
            unsigned sender = 1;
            static int level = 5;
            static float flow = 1.f;
            memcpy(&udpData[0], &id, 4);
            memcpy(&udpData[4], &sender, 4);
            memcpy(&udpData[8], &level, 4);
            memcpy(&udpData[12], &flow, 4);
            MessageUDP udpMessage(51, (MessageUDP::IPAddr){192,168,1,255}, 9001, udpData, 16);

            OS_API::sendUdpMessage(udpMessage);

            if(isLevelRising)
            {
                if(level <= 35)
                {
                    level += 2;
                }else
                {
                    isLevelRising = false;
                }
            }else
            {
                if(level > 0)
                {
                    level -= 2;
                }else
                {
                    isLevelRising = true;
                }
            }


            if(isFlowRising)
            {
                if(flow <= 24)
                {
                    flow += 2.3f;
                }else
                {
                    isFlowRising = false;
                }
            }else{
                if(flow > 0)
                {
                    flow -= 1.4f;
                }else
                {
                    isFlowRising = true;
                }
            }


            cyclicsToGo = 25;          

            packagesSent ++;      
            needsUpdate = true;
        }
            cyclicsToGo--;

    }
    virtual void render(DisplayProvider& display) override{
        if(needsUpdate)
        {
            display.fillScreen(getBackgroundColor());
            display.setTextSize(1);
            display.setTextColor(TFT_BLACK, getBackgroundColor());

            display.drawString("UDP Package testing ", 70, 30);  

            display.drawString("Packages sent : " + String(packagesSent), 70, 70);  
            display.drawString("Packages received : " + String(packagesReceived), 70, 110);  

            needsUpdate = false;
        }
    }
    virtual void end() override{

    }

    void udpDataReceived(int messageID, std::vector<uint8_t> data) {
        packagesReceived ++;
        needsUpdate = true;

    }

    virtual String getAppNameString() override
    {
        return "UDP Test App";
    }
    uint16_t getBackgroundColor(){
        return TFT_WHITE;
    }
};



#endif
