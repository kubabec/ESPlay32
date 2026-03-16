#include "app/games/HumanRun.h"

HumanRun::HumanRun()
{
}

void HumanRun::start(int w, int h)
{
    initializeGame(gameArray[0], 0, 15, 10);
    appHeight = h;
    appWidth = w;
    for (int g = 0; g < 5; g++)
    {
        gameArray[0].obstacles[g].x = appWidth + obstacleWidth;
        gameArray[0].obstacles[g].oldX = appWidth + obstacleWidth;
    }
}

void HumanRun::input(InputType input)
{
    if (input == InputType::BUTTON_C)
    {
        processButton(gameArray[0]);
    }
}

void HumanRun::longPressInput(InputType input)
{
}

void HumanRun::longPressRelease(InputType input)
{
}

void HumanRun::analogInput(int x, int y)
{
}

void HumanRun::udpDataReceived(int messageID, std::vector<uint8_t> data)
{
}

void HumanRun::touchInput(int x, int y)
{
}

void HumanRun::update()
{
    static long timer = 0;
    if (millis() - timer > 100)
    {
        int gamesCount = (gameMode == DUEL) ? 2 : 1;
        for (int i = 0; i < gamesCount; i++)
        {
            processGame(gameArray[i]);
        }
        timer = millis();
    }
}
void HumanRun::renderObstacle(int indeks, DisplayProvider &display)
{
    if (gameArray[0].obstacles[indeks].oldX != gameArray[0].obstacles[indeks].x)
    {
        display.fillCircle(gameArray[0].obstacles[indeks].oldX, appHeight - 50, 50, getBackgroundColor());
        gameArray[0].obstacles[indeks].oldX = gameArray[0].obstacles[indeks].x;
        display.fillCircle(gameArray[0].obstacles[indeks].x, appHeight - 50, 50, TFT_BLUE);
    }
}
void HumanRun::render(DisplayProvider &display)
{
    for (int i = 0; i < 1; i++)
    {
        if (gameArray[0].obstacles[i].isActive)
        {
            renderObstacle(i, display);
        }
    }
    // display.fillCircle(100,appHeight-50,50,TFT_BLUE);
}

void HumanRun::forceRender(DisplayProvider &display)
{
}

void HumanRun::end()
{
}

String HumanRun::getAppNameString()
{
    return "Human Run";
}

uint16_t HumanRun::getBackgroundColor()
{
    return TFT_BLACK;
}

bool HumanRun::isObstOnPlayerX(Game &game)
{
    for (int i = 0; i < 5; i++)
    {
        if (game.obstacles[i].x == game.player.posX)
        {
            return true;
        }
    }
    return false;
}

bool HumanRun::isCollision(Game &game)
{
    if (isObstOnPlayerX(game) && (game.player.state == RUNNING1 || game.player.state == RUNNING2))
    {
        return true;
    }
    return false;
}

void HumanRun::resetGameOver(Game &game)
{
    game.player.score = 0;
    game.player.state = RUNNING1;
    for (int i = 0; i < 5; i++)
    {
        game.obstacles[i].x = game.boardEndX;
        game.obstacles[i].isActive = false;
    }
    gamesOverCount--;
    game.isGameOver = false;
}

void HumanRun::processObstacleMove(Game &game)
{
    for (int i = 0; i < 5; i++)
    {
        if (game.obstacles[i].isActive == true)
        {
            if (game.obstacles[i].x > 0)
            {
                game.obstacles[i].oldX = game.obstacles[i].x;
                game.obstacles[i].x -= 10;
            }
            else
            {
                game.obstacles[i].oldX = game.obstacles[i].x;
                game.obstacles[i].x = game.boardEndX;
                game.obstacles[i].isActive = false;
            }
        }
    }
}

void HumanRun::processHumanMove(Game &game)
{
    switch (game.player.state)
    {
    case RUNNING1:
        game.player.state = RUNNING2;
        break;

    case RUNNING2:
        game.player.state = RUNNING1;
        break;

    case JUMP_START:
        if (game.stateCompleted == true)
        {
            game.player.state = JUMP;
            game.stateCompleted = false;
        }
        else
        {
            game.stateCompleted = true;
        }
        break;

    case JUMP:
        if (game.stateCompleted == true)
        {
            game.player.state = JUMP_DOWN;
            game.stateCompleted = false;
        }
        else
        {
            game.stateCompleted = true;
        }
        break;

    case JUMP_DOWN:
        if (game.stateCompleted == true)
        {
            game.player.state = RUNNING1;
            game.stateCompleted = false;
        }
        else
        {
            game.stateCompleted = true;
        }
        break;
    }
}

void HumanRun::initializeGame(Game &game, int begin, int end, int btnPin)
{
    game.boardBeginX = begin;
    game.boardEndX = end;
    game.player.posX = begin + 2;
    for (int i = 0; i < 5; i++)
    {
        game.obstacles[i].x = game.boardEndX;
    }
    game.buttonPin = btnPin;
}

void HumanRun::processButton(Game &game)
{
    if (game.player.state == RUNNING1 || game.player.state == RUNNING2)
    {
        game.player.state = JUMP_START;
    }
    if (game.isGameOver == true)
    {
        resetGameOver(game);
    }
}

void HumanRun::processScore(Game &game)
{
    for (int i = 0; i < 5; i++)
    {
        if (game.obstacles[i].isActive && game.obstacles[i].x == (game.player.posX - 1))
        {
            game.player.score++;
        }
    }
}

void HumanRun::generateObstacle(Game &game)
{
    for (int i = 0; i < 5; i++)
    {
        if (game.obstacles[i].isActive == false)
        {
            game.obstacles[i].isActive = true;
            int randValue = random(200);
            while (randValue < 2 || randValue == 4)
            {
                randValue = random(200);
            }
            game.ticksToGenerateNewObst = randValue;
            return;
        }
    }
}

void HumanRun::processGame(Game &game)
{
    if (game.isGameOver == false)
    {
        processObstacleMove(game);
        if (game.ticksToGenerateNewObst == 0)
        {
            generateObstacle(game);
        }
        game.ticksToGenerateNewObst--;
        processHumanMove(game);
        processScore(game);
        game.isGameOver = isCollision(game);
        if (game.isGameOver == true)
        {
            gamesOverCount++;
            return;
        }
        
    }
}
