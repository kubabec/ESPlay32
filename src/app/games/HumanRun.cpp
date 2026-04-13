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
    calculateCollisionPoints();
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
    if (millis() - timer > 10)
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
        display.fillCircle(gameArray[0].obstacles[indeks].oldX, appHeight - OBSTACLE_SIZE, OBSTACLE_SIZE, getBackgroundColor());
        gameArray[0].obstacles[indeks].oldX = gameArray[0].obstacles[indeks].x;
        display.fillCircle(gameArray[0].obstacles[indeks].x, appHeight - OBSTACLE_SIZE, OBSTACLE_SIZE, TFT_BLUE);
    }
}
void HumanRun::render(DisplayProvider &display)
{
    if (gameArray[0].player.oldY != gameArray[0].player.posY)
    {
        renderPlayer(display, TFT_BLACK, TFT_BLACK, gameArray[0].player.oldY);
    }
    renderPlayer(display, TFT_GOLD, TFT_PURPLE, gameArray[0].player.posY);
    for (int i = 0; i < 5; i++)
    {
        if (gameArray[0].obstacles[i].isActive)
        {
            renderObstacle(i, display);
        }
    }

    if (gameArray[0].isGameOver)
    {
        display.drawLine(point1.x, point1.y, point2.x, point2.y, TFT_RED);
    }
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

float distance2D(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

bool HumanRun::isCollision(Game &game)
{
    for (int i = 0; i < 5; i++)
    {
        if (game.obstacles[i].isActive == false)
        {
            continue;
        }
        for (CollisionPoint &point : collisionPoints)
        {
            float distance = distance2D(point.x,point.y,game.obstacles[i].x, getY(game.obstacles[i].radius));

            // std::cout << elementWektora << " ";

            if (distance < game.obstacles[i].radius)
            {
                Serial.println("distance: "+ String(distance)+ "radius: " + String(game.obstacles[i].radius));
                point1 = CollisionPoint(point.x, point.y);
                point2 = CollisionPoint(game.obstacles[i].x, getY(game.obstacles[i].radius));

                return true;
            }
        }
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
            if (game.obstacles[i].x > -60)
            {
                game.obstacles[i].oldX = game.obstacles[i].x;
                game.obstacles[i].x -= 5;
            }
            else
            {
                game.obstacles[i].oldX = appWidth + obstacleWidth;
                game.obstacles[i].x = appWidth + obstacleWidth;
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

    case JUMP:
        if (gameArray[0].player.posY < 150)
        {
            gameArray[0].player.oldY = gameArray[0].player.posY;
            gameArray[0].player.posY += 5;
        }
        else
        {
            gameArray[0].player.state = JUMP_DOWN;
        }
        calculateCollisionPoints();
        break;

    case JUMP_DOWN:
        if (gameArray[0].player.posY > 0)
        {
            gameArray[0].player.oldY = gameArray[0].player.posY;
            gameArray[0].player.posY -= 5;
        }
        else
        {
            gameArray[0].player.oldY = 0;
            gameArray[0].player.state = RUNNING1;
        }
        calculateCollisionPoints();
        break;
    }
}

void HumanRun::initializeGame(Game &game, int begin, int end, int btnPin)
{
    game.boardBeginX = begin;
    game.boardEndX = end;
    game.player.posX = 100;
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
        game.player.state = JUMP;
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
        Serial.println("Looking for empty obstacle slot");
        if (game.obstacles[i].isActive == false)
        {
            game.obstacles[i].isActive = true;
            int randValue = random(30);
            randValue += ((OBSTACLE_SIZE / 10) + 15);

            game.ticksToGenerateNewObst = randValue;
            Serial.println("Generating new obstacle!");
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

int HumanRun::getY(float y)
{
    return appHeight - (int)y;
}

void HumanRun::renderPlayer(DisplayProvider &display, uint32_t bodyColor, uint32_t headColor, int y)
{
    const float playerHeight = 100;
    const float headRadius = playerHeight * 0.20;
    const float armHeight = playerHeight * 0.15;
    const float bodyHeight = playerHeight * 0.35;
    const float legHeight = playerHeight * 0.3;

    const float playerWidth = 60;
    const float handWidth = playerWidth * 0.5;
    const float bodyWidth = playerWidth * 0.3;
    const float legWidth = playerWidth * 0.5;
    int x = gameArray[0].player.posX;
    // Right leg
    display.drawLine(x, getY(legHeight + y), x + (int)(legWidth * 0.5), getY(y), bodyColor);
    display.drawLine(x + (int)(legWidth * 0.5), getY(y), x + (int)(legWidth), getY(5 + y), bodyColor);
    display.drawLine(x + (int)(legWidth * 0.5), getY(legHeight + y), x + (int)(legWidth), getY(5 + y), bodyColor);

    // Body right side
    display.drawLine(x + (int)(legWidth * 0.5), getY(legHeight + y), x + (int)(legWidth * 0.5), getY(legHeight + bodyHeight + y), bodyColor);
    display.drawLine(x + (int)(legWidth * 0.5), getY(legHeight + bodyHeight + y), x + handWidth, getY(legHeight + (bodyHeight * 0.4) + y), bodyColor);
    display.drawLine(x + handWidth, getY(legHeight + (bodyHeight * 0.4) + y), x + handWidth + (handWidth * 0.4), getY(legHeight + (bodyHeight * 0.64) + y), bodyColor);
    display.drawLine(x + handWidth + (handWidth * 0.4), getY(legHeight + (bodyHeight * 0.64) + y), x + bodyWidth, getY(legHeight + bodyHeight + armHeight + y), bodyColor);

    // Neck
    display.drawLine(x + bodyWidth, getY(legHeight + bodyHeight + armHeight + y), x - bodyWidth, getY(legHeight + bodyHeight + armHeight + y), bodyColor);

    // Body left side
    display.drawLine(x - (int)(legWidth * 0.5), getY(legHeight + y), x - (int)(legWidth * 0.5), getY(legHeight + bodyHeight + y), bodyColor);
    display.drawLine(x - (int)(legWidth * 0.5), getY(legHeight + bodyHeight + y), x - handWidth, getY(legHeight + (bodyHeight * 0.4) + y), bodyColor);
    display.drawLine(x - handWidth, getY(legHeight + (bodyHeight * 0.4) + y), x - handWidth - (handWidth * 0.4), getY(legHeight + (bodyHeight * 0.64) + y), bodyColor);
    display.drawLine(x - handWidth - (handWidth * 0.4), getY(legHeight + (bodyHeight * 0.64) + y), x - bodyWidth, getY(legHeight + bodyHeight + armHeight + y), bodyColor);

    // Left leg
    display.drawLine(x, getY(legHeight + y), x - (int)(legWidth * 0.5), getY(y), bodyColor);
    display.drawLine(x - (int)(legWidth * 0.5), getY(y), x - (int)(legWidth), getY(5 + y), bodyColor);
    display.drawLine(x - (int)(legWidth * 0.5), getY(legHeight + y), x - (int)(legWidth), getY(5 + y), bodyColor);

    // Head
    display.fillCircle(x, getY(y + legHeight + bodyHeight + armHeight + headRadius + 1), headRadius, headColor);

    // display.drawLine(x + (int)(legWidth * 0.5), getY(y), gameArray[0].obstacles[indeks].x, appHeight - OBSTACLE_SIZE, TFT_RED);
    // display.drawLine(x + (int)(legWidth * 0.5), getY(legHeight + y), gameArray[0].obstacles[indeks].x, appHeight - OBSTACLE_SIZE, TFT_RED);
    // display.drawLine(x + handWidth, getY(legHeight + (bodyHeight * 0.4) + y), gameArray[0].obstacles[indeks].x, appHeight - OBSTACLE_SIZE, TFT_RED);
    // display.drawLine(x - handWidth, getY(legHeight + (bodyHeight * 0.4) + y), gameArray[0].obstacles[indeks].x, appHeight - OBSTACLE_SIZE, TFT_RED);
    // display.drawLine(x - (int)(legWidth * 0.5), getY(y), gameArray[0].obstacles[indeks].x, appHeight - OBSTACLE_SIZE, TFT_RED);
    // display.drawLine(x - (int)(legWidth * 0.5), getY(legHeight + y), gameArray[0].obstacles[indeks].x, appHeight - OBSTACLE_SIZE, TFT_RED);
}

void HumanRun::calculateCollisionPoints()
{
    const float playerHeight = 100;
    const float headRadius = playerHeight * 0.20;
    const float armHeight = playerHeight * 0.15;
    const float bodyHeight = playerHeight * 0.35;
    const float legHeight = playerHeight * 0.3;

    const float playerWidth = 60;
    const float handWidth = playerWidth * 0.5;
    const float bodyWidth = playerWidth * 0.3;
    const float legWidth = playerWidth * 0.5;
    int x = gameArray[0].player.posX;
    int y = gameArray[0].player.posY;
    collisionPoints = {
        {x + (int)(legWidth * 0.5), getY(y)},
        {x + (int)(legWidth), getY(5 + y)},
        {x + handWidth, getY(legHeight + (bodyHeight * 0.4) + y)},
        {x + handWidth + (handWidth * 0.4), getY(legHeight + (bodyHeight * 0.64) + y)},
        {x - (int)(legWidth * 0.5), getY(y)},
        {x - (int)(legWidth), getY(5 + y)},
        {x - handWidth, getY(legHeight + (bodyHeight * 0.4) + y)},
        {x - handWidth - (handWidth * 0.4), getY(legHeight + (bodyHeight * 0.64) + y)}};
}