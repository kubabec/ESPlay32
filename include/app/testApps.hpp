#ifndef TESTAPPS_H
#define TESTAPPS_H
#include <app/runtimeApplication.hpp>
#include <os/menu.hpp>


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
    void udpDataReceived(std::vector<uint8_t> data) {}

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

    void udpDataReceived(std::vector<uint8_t> data) {}

    virtual String getAppNameString() override
    {
        return "Touch test";
    }
    uint16_t getBackgroundColor(){
        return TFT_WHITE;
    }
};

#endif
