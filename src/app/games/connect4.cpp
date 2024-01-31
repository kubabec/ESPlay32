#include "app/games/connect4.h"

Connect4::Connect4()
{
//    touchProxy.addTouchArea(10, 10, 200, 200, std::bind(&Connect4::touchCallback, this, std::placeholders::_1), 1);
    int currentFieldX = 15;
    for(int i = 0; i < horizontalFieldsCount; i++) {
        touchProxy.addTouchArea(currentFieldX, // x
                                5, // y
                                horizontalFieldWidth, // w
                                295, // h
                                std::bind(&Connect4::touchCallback, this, std::placeholders::_1),
                                i);
        currentFieldX += horizontalFieldWidth + 5;
    }
}

void Connect4::start(int w, int h)
{

}

void Connect4::input(InputType input)
{

}

void Connect4::longPressInput(InputType input)
{

}

void Connect4::longPressRelease(InputType input)
{

}

void Connect4::analogInput(int x, int y)
{

}

void Connect4::touchInput(int x, int y)
{
    touchProxy.touchInput(x, y);
}

void Connect4::update()
{

}

void Connect4::render(DisplayProvider &display)
{
//    display.fillRect(10, 10, 200, 200, TFT_WHITE);
    if (!isBgDrawn) {
        drawGameboardBg(display);
    }
    for (auto& ball : ballVector) {
        ball.draw(display);
    }
}

void Connect4::end()
{

}

String Connect4::getAppNameString()
{
    return "Connect 4";
}

uint16_t Connect4::getBackgroundColor()
{
    return TFT_BLACK;
}

void Connect4::touchCallback(int touchID)
{
//    ballVector.push_back(Character2D(35 + touchID * (horizontalFieldWidth + 5), 30, (horizontalFieldWidth / 2) - 2));
    if (gameState == PLAYER_1_TURN || gameState == PLAYER_2_TURN) {
        uint8_t targetRowNumber = gameBoard.makeMove((gameState == PLAYER_1_TURN), touchID);
        ballVector.push_back(Character2D(35 + touchID * (horizontalFieldWidth + 5),
                                         30 + (targetRowNumber * 40),
                                         (horizontalFieldWidth / 2) - 2));
    }
}

void Connect4::drawGameboardBg(DisplayProvider &display)
{
    int currentFieldX = 10;
    for(int i = 0; i < horizontalFieldsCount + 1; i++) {
        display.fillRect(currentFieldX, 80, 5, 220, TFT_RED);
        currentFieldX += horizontalFieldWidth + 5;
    }
    isBgDrawn = true;
}

GameBoardData::GameBoardData(uint8_t numColumns, uint8_t numRows)
{
    columns = numColumns;
    rows = numRows;
    gameField2DArray = new GameField*[numColumns];

    for(int i = 0; i < numColumns; i ++) {
        gameField2DArray[i] = new GameField[numRows];
    }
}

GameBoardData::~GameBoardData()
{
    for(int i = 0; i < columns; i ++) {
        delete gameField2DArray[i];
    }

    delete gameField2DArray;
}

uint8_t GameBoardData::makeMove(bool isPlayer1Turn, uint8_t touchedColumn)
{
    uint8_t emptyFieldID = getFirstEmptyField(touchedColumn);
    if (emptyFieldID != 255) {
        gameField2DArray[touchedColumn][emptyFieldID].assignField(isPlayer1Turn);
    }
    return rows - emptyFieldID;
}

uint8_t GameBoardData::getFirstEmptyField(uint8_t columnID)
{
    for (int i = 0; i < rows; i++) {
        if (gameField2DArray[columnID][i].isFree()) {
            return i;
        }
    }
    return 255;
}

GameField::GameField()
{

}

bool GameField::isFree()
{
    if (myState == FREE) {
        return true;
    }
    return false;
}

void GameField::assignField(bool isPlayer1)
{
    if (isPlayer1) {
        myState = TAKEN_BY_PLAYER_1;
    }
    else {
        myState = TAKEN_BY_PLAYER_2;
    }
}
