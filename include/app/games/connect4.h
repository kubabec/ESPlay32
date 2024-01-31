#ifndef CONNECT4_H
#define CONNECT4_H

#include <app/runtimeApplication.hpp>
#include <app/tools/touchinputproxy.h>
#include <app/tools/character2d.hpp>

typedef enum {
    PLAYER_1_TURN,
    PLAYER_2_TURN,
    BALL_FALLING
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
};

class GameBoardData
{
public:
    GameBoardData(uint8_t numColumns, uint8_t numRows);
    ~GameBoardData();
    uint8_t makeMove(bool isPlayer1Turn, uint8_t touchedColumn);
private:
    GameField** gameField2DArray;
    uint8_t columns = 0;
    uint8_t rows = 0;

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

    bool isBgDrawn = false;
    int verticalFieldsCount = 7;
    int horizontalFieldsCount = 7;
    const int horizontalFieldWidth = 40;

    std::vector<Character2D> ballVector;

    Connect4GameState gameState = PLAYER_1_TURN;
    GameBoardData gameBoard{7, 5};
};

#endif // CONNECT4_H
