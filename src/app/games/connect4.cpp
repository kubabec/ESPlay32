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

void Connect4::udpDataReceived(std::vector<uint8_t> data) {

}

void Connect4::touchInput(int x, int y)
{
    touchProxy.touchInput(x, y);
}

void Connect4::update()
{
    if(gameState == BALL_FALLING) {
        currentFallingBall.moveBy(0, 5);
        if (currentFallingBall.getY() == targetYFallingBall) {
            if(wasPlayerOneTurn) {
                gameState = PLAYER_2_TURN;
                wasPlayerOneTurn = false;
            }
            else {
                gameState = PLAYER_1_TURN;
                wasPlayerOneTurn = true;
            }
        }
    }
    whoWon = checkIfGameFinished();
    if (whoWon != 0 && gameState != BALL_FALLING) {
        gameState = CONNECT_4_OVER;
    }

}

void Connect4::render(DisplayProvider &display)
{
//    display.fillRect(10, 10, 200, 200, TFT_WHITE);
    if (gameState != CONNECT_4_OVER) {
        if (!isBgDrawn) {
            drawGameboardBg(display);
        }
        currentFallingBall.draw(display);
        display.setTextSize(1);
        if(wasPlayerOneTurn) {
            display.setTextColor(TFT_YELLOW, getBackgroundColor());
        }
        else {
            display.setTextColor(TFT_WHITE, getBackgroundColor());
        }
        display.drawString("Player 1", 350, 100);
        if(wasPlayerOneTurn) {
            display.setTextColor(TFT_WHITE, getBackgroundColor());
        }
        else {
            display.setTextColor(TFT_YELLOW, getBackgroundColor());
        }
        display.drawString("Player 2", 350, 140);
    }
    else {
        if (whoWon == 1) {
            display.fillScreen(TFT_BLACK);
            display.drawString("Player 1 won!", 150, 140);
        }
        else if (whoWon == 2) {
            display.fillScreen(TFT_BLACK);
            display.drawString("Player 2 won!", 150, 140);
        }
        else {
            display.drawString("error", 150, 140);
        }
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
    if (gameState == PLAYER_1_TURN || gameState == PLAYER_2_TURN) {
        uint8_t targetRowNumber = gameBoard.makeMove((gameState == PLAYER_1_TURN), touchID);
        if (targetRowNumber != 255) {
            if (gameState == PLAYER_1_TURN) {
                currentFallingBall.setColor(TFT_CYAN);
            }
            else {
                currentFallingBall.setColor(TFT_RED);
            }
            currentFallingBall.move(35 + touchID * (horizontalFieldWidth + 5), 25);
            currentFallingBall.setLastXandY(500, 500);
            targetYFallingBall = 20 + (targetRowNumber * 40);
            gameState = BALL_FALLING;
        }
    }
}

void Connect4::drawGameboardBg(DisplayProvider &display)
{
    int currentFieldX = 10;
    for(int i = 0; i < horizontalFieldsCount + 1; i++) {
        display.fillRect(currentFieldX, 40, 5, 260, TFT_WHITE);
        currentFieldX += horizontalFieldWidth + 5;
    }
    isBgDrawn = true;
}

uint8_t Connect4::checkIfGameFinished()
{
    return gameBoard.checkGameOver();
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
        return rows - emptyFieldID;
    }
    return 255;
}

bool GameBoardData::checkIfGameFinished()
{
    bool isWin = false;
    isWin |= checkIfVerticalWin();
//    isWin |= checkIfDiagonalWin();
//    isWin |= checkIfHorizontalWin();
    return isWin;
}

bool GameBoardData::checkIfVerticalWin()
{
    for (int col = 0; col < columns; col++) {
        for (int row = 0; row < (rows + 1) - 4; row++) {
            if (gameField2DArray[col][row].isTakenByPlayer1() &&
                gameField2DArray[col][row + 1].isTakenByPlayer1() &&
                gameField2DArray[col][row + 2].isTakenByPlayer1() &&
                gameField2DArray[col][row + 3].isTakenByPlayer1()) {
                didPlayerOneWin = true;
                return true;
            }
            if (gameField2DArray[col][row].isTakenByPlayer2() &&
                gameField2DArray[col][row + 1].isTakenByPlayer2() &&
                gameField2DArray[col][row + 2].isTakenByPlayer2() &&
                gameField2DArray[col][row + 3].isTakenByPlayer2()) {
                didPlayerOneWin = false;
                return true;
            }
        }
    }
    return false;
}

bool GameBoardData::checkIfDiagonalWin()
{
    for (int col = 0; col < columns; col++) {
        for (int row = 0; row < (rows + 1) - 4; row++) {
            if (gameField2DArray[col][row].isTakenByPlayer1() &&
                gameField2DArray[col + 1][row + 1].isTakenByPlayer1() &&
                gameField2DArray[col + 2][row + 2].isTakenByPlayer1() &&
                gameField2DArray[col + 3][row + 3].isTakenByPlayer1()) {
                return true;
            }
            if (gameField2DArray[col][row].isTakenByPlayer2() &&
                gameField2DArray[col + 1][row + 1].isTakenByPlayer2() &&
                gameField2DArray[col + 2][row + 2].isTakenByPlayer2() &&
                gameField2DArray[col + 3][row + 3].isTakenByPlayer2()) {
                return true;
            }
        }
    }
    return false;
}

uint8_t GameBoardData::checkGameOver()
{
    if (checkIfGameFinished()) {
        if (didPlayerOneWin) {
            return 1;
        }
        else {
            return 2;
        }
    }
    else {
        return 0;
    }
}

bool GameBoardData::checkIfHorizontalWin()
{
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < (col + 1) - 4; col++) {
            if (gameField2DArray[col][row].isTakenByPlayer1() &&
                gameField2DArray[col + 1][row].isTakenByPlayer1() &&
                gameField2DArray[col + 2][row].isTakenByPlayer1() &&
                gameField2DArray[col + 3][row].isTakenByPlayer1()) {
                return true;
            }
            if (gameField2DArray[col][row].isTakenByPlayer2() &&
                gameField2DArray[col + 1][row].isTakenByPlayer2() &&
                gameField2DArray[col + 2][row].isTakenByPlayer2() &&
                gameField2DArray[col + 3][row].isTakenByPlayer2()) {
                return true;
            }
        }
    }
    return false;
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

bool GameField::isTakenByPlayer1()
{
    return myState == TAKEN_BY_PLAYER_1;
}

bool GameField::isTakenByPlayer2()
{
    return myState == TAKEN_BY_PLAYER_2;
}
