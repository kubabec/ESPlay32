#ifndef CONNECT4_H
#define CONNECT4_H

#include <app/runtimeApplication.hpp>
#include <app/tools/touchinputproxy.h>
#include <app/tools/character2d.hpp>

typedef enum {
    PLAYER_1_TURN,
    PLAYER_2_TURN,
    BALL_FALLING,
    CONNECT_4_OVER
}Connect4GameState;

class GameField
{
    typedef enum {
        TAKEN_BY_PLAYER_1,
        TAKEN_BY_PLAYER_2,
        FREE
    }FieldState;
    FieldState myState = FREE;

public:
    GameField();

    bool isFree();
    void assignField(bool isPlayer1);
    bool isTakenByPlayer1();
    bool isTakenByPlayer2();
};

class GameBoardData
{
public:
    GameBoardData(uint8_t numColumns, uint8_t numRows);
    ~GameBoardData();
    uint8_t makeMove(bool isPlayer1Turn, uint8_t touchedColumn);
    bool checkIfGameFinished();
    bool checkIfVerticalWin();
    bool checkIfHorizontalWin();
    bool checkIfDiagonalWin();
    uint8_t checkGameOver();

private:
    GameField** gameField2DArray;
    uint8_t columns = 0;
    uint8_t rows = 0;
    bool didPlayerOneWin = false;

    uint8_t getFirstEmptyField(uint8_t columnID);
};

class Connect4 : public RuntimeApplication
{
    TouchInputProxy touchProxy;
public:
    Connect4();

    // RuntimeApplication interface
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
private:
    void touchCallback(int touchID);
    void drawGameboardBg(DisplayProvider &display);
    uint8_t checkIfGameFinished();

    bool isBgDrawn = false;
    int verticalFieldsCount = 7;
    int horizontalFieldsCount = 7;
    const int horizontalFieldWidth = 40;

    float targetYFallingBall = 0;

    bool wasPlayerOneTurn = true;

    uint8_t whoWon = 0;

    Character2D currentFallingBall{500, 500, static_cast<uint8_t>(((horizontalFieldWidth / 2) - 2))};

    Connect4GameState gameState = PLAYER_1_TURN;
    GameBoardData gameBoard{7, 6};
};

#endif // CONNECT4_H
