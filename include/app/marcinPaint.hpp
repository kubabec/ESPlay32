#ifndef MARCINPAINT_H
#define MARCINPAINT_H
#include "app/runtimeApplication.hpp"
#include "app/tools/button.hpp"
#include <vector>

class MarcinPaint : public RuntimeApplication {
    public:
    
    std::vector<Button> vec_buttons;

    bool isDrawing = false;

    struct Point {
        int x;
        int y;
    };
    std::vector<Point> drawingPoints;

    MarcinPaint();
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

    int x, y, w, h;
    int backgroundcolor = TFT_WHITE;
    int clearScreen = true;
    int ballCol = TFT_BLACK;

    bool isScreenDrawn = false;

    

};

#endif