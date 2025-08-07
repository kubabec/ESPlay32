#ifndef MARCINAPP_H
#define MARCINAPP_H
#include "app/runtimeApplication.hpp"

class MarcinApp : public RuntimeApplication {
    public:
    
    MarcinApp();
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
    private:

    int x, y;
    int backgroundcolor = TFT_BLACK;
    int ballCol = TFT_BLACK;
    int colours [5] { TFT_RED, TFT_YELLOW, TFT_BLUE, TFT_GREEN, TFT_BLACK};
    int indexColour = 0;
    int ballColours [5] {TFT_BLUE, TFT_YELLOW, TFT_RED, TFT_GREEN, TFT_WHITE};
    bool changeScreenColour = true;
    bool changeBallColour = true; 

    bool isBgDrawn = false;
    int verticalFieldsCount = 7;
    int numberOfLines = 5;
    const int horizontalFieldWidth = 60;
    int lengthVertical = 3;         // thickness of vertical line
    int heightVertical = 255;       // length of vertical line
    int lengthHorizontal = 255;     // length of horizontal line
    int heightHorizontal = 3;       // thickness of horizontal line 

    void drawGameboardBg(DisplayProvider &display);

    
    
};

#endif