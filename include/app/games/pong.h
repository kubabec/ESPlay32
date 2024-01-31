#ifndef PONG_H
#define PONG_H

#include <os/menu.hpp>

typedef enum {
    GAME_PLAYING,
    GAME_STOPPED
}StanGry;

typedef enum {
    PONG_SINGLE,
    PONG_DUEL,
    PONG_MULTI
}TypGry;

#include <app/runtimeApplication.hpp>
#include <app/tools/vector2d.hpp>
#include <app/tools/character2d.hpp>
#define SPEED_INCREMENT_VAL 7

class BouncePlatform {
public:
    BouncePlatform(float x, float y, float w, float h, bool right);
    bool reflect(Character2D& character);
    void draw(DisplayProvider& display);
    void update();
    float getReflectionX();
    float getTopY();
    float getBottomY();
    float getHeight();
    float getWidth();
    void btnUpPressed();
    void btnDownPressed();
private:
    Vector2D pos;
    Vector2D lastPosDiff;
    float width, height;
    float moveStep = 1;
    bool lastDiffChanged = false;
    bool isRight = false;
    int speed = 0;
    int lastSpeed = 0;
    const uint8_t maxSpeedAbs = 10;
    bool isBtnPressed = false;
    bool maxYreached = false;
    bool minYreached = false;



    void moveUp(uint8_t pixels);
    void moveDown(uint8_t pixels);
};

class Pong : public RuntimeApplication
{
public:
    Pong(bool isMulti);
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
private:
    int8_t submenuSelection = -1;
    BouncePlatform platformLeft{10, 100, 20, 70, false};
    BouncePlatform platformRight{450, 120, 20, 70, true};
    Character2D ball{237, 147, 6};
    bool isButtonTopPressed = false, isButtonBottomPressed = false;
    float ballResetX, ballResetY;
    bool ballResetPending = false;
    void detectEdgeReflections();
    void detectBouncePlatformsReflection();
    void handleRightPlatformMoveOnButtonsPressed();
    void gameReset();
    void checkIfScoreAchieved();
    void updateOverlayText();
    void randomizeBallDir();

    float speed = 4.f;
    const uint8_t maxSpeed = 6.f;
    int scoreLeft = 0;
    int scoreRight = 0;
    String overlayText = "";
    int ballColor = 0;
    StanGry stanGry = GAME_STOPPED;
    String countdown = "0";

    bool resetScreenPending = true;
    bool countdownClearPending = false;
};

class PongLauncher : public RuntimeApplication
{
    typedef enum{
        NOT_SELECTED = -1,
        SINGLEPLAYER_SELECTED = -256,
        DUEL_SELECTED = -255,
        MULTIPLAYER_SELECTED = -254
    }GameSelectionState;
    GameSelectionState selectionState = NOT_SELECTED;
    Menu pongMainMenu{{"Pong single", "Pong duel", "Pong multi"}};
    Pong* pongGamePtr = nullptr;
public:
    PongLauncher();
    ~PongLauncher();
    void start(int w, int h);
    void input(InputType input);
    void longPressInput(InputType input);
    void longPressRelease(InputType input);
    void analogInput(int x, int y);
    void touchInput(int x, int y);
    void update();
    void render(DisplayProvider &display);
    void end();
    String getAppNameString();
    uint16_t getBackgroundColor();
};

#endif // PONG_H
