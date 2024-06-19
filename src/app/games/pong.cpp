#include "app/games/pong.h"
#include "os/portableos.hpp"

Pong::Pong(bool isMulti)
{
    ball.setColor(TFT_WHITE);

    randomizeBallDir();


}

void Pong::start(int w, int h)
{
    ball.setCharacterMoveRanges(0-ball.getSize()*2 - 2, 0, w+ball.getSize()*2+2, h);
}

void Pong::udpDataReceived(int messageID, std::vector<uint8_t> data) {

}

void Pong::input(InputType input)
{
    // switch (input) {
    //     case BUTTON_A:
    //         //platformRight.moveUp();
    //     break;
    //     case BUTTON_C:
    //         //platformRight.moveDown();
    //     break;
    // }

    // Notification emptyNotif {
    //     .title = "empty",
    //     .text = "Random text here",
    //     .bgcolor = TFT_YELLOW
    // };
    // OS_API::pushNotification(emptyNotif);
}

void Pong::longPressInput(InputType input)
{
    switch(input)
    {
        case BUTTON_A:
            isButtonTopPressed = true;
        break;

        case BUTTON_C:
            isButtonBottomPressed = true;
        break;

        default: break;
    }
}

void Pong::longPressRelease(InputType input)
{
    switch(input)
    {
        case BUTTON_A:
            isButtonTopPressed = false;
        break;

        case BUTTON_C:
            isButtonBottomPressed = false;
        break;

        default: break;
    }
}

void Pong::analogInput(int x, int y)
{
     y = y * -1;
     if(y > 2) {
         platformLeft.btnDownPressed();
     }
     else if(y < -2) {
         platformLeft.btnUpPressed();
     }

}

void Pong::touchInput(int x, int y)
{

}

void Pong::update()
{
    static uint8_t counter = 0;

    // Handle right platform move when button on keyboard is pressed
    handleRightPlatformMoveOnButtonsPressed();

    // real - time limits of ball move areas to do not fall inside the platforms
    ball.clearSquareMoveLimitAreas();
    std::vector<SquareMoveLimitArea> ballMoveLimits;
    ballMoveLimits.push_back(
                SquareMoveLimitArea{
                             platformRight.getReflectionX(),
                             platformRight.getTopY(),
                             platformRight.getWidth(),
                             platformRight.getHeight()});

    ballMoveLimits.push_back(
                SquareMoveLimitArea{
                             platformLeft.getReflectionX()-platformLeft.getWidth(),
                             platformLeft.getTopY(),
                             platformLeft.getWidth(),
                             platformLeft.getHeight()});

    ball.setNewSquareMoveLimitAreas(ballMoveLimits);

    switch (stanGry) {
    case GAME_PLAYING:
        ball.update();
        static uint8_t countTo4 = 0;
        if(countTo4 >= 4){
            segmentedBackground.setStickySegment((uint16_t)ball.getLastX(), (uint16_t)ball.getLastY());
            segmentedBackground.setStickySegment((uint16_t)ball.getX(), (uint16_t)ball.getY());
            countTo4 = 0;
        }
        countTo4 ++;
        break;
    case GAME_STOPPED:
        if (counter >= 60) {
            counter = 0;
            countdownClearPending = true;
            stanGry = GAME_PLAYING;
        }
        else {
            counter++;
            if (counter <= 20) {
                countdown = "3";
            }
            else if (counter <= 40) {
                countdown = "2";
            }
            else {
                countdown = "1";
            }
        }
        break;
    }
    // Update platforms movement
    platformLeft.update();
    platformRight.update();


    // Check if ball is reflected by platforms
    detectBouncePlatformsReflection();

    // Check if ball is reflected by top or bottom edge of the display
    detectEdgeReflections();

    // Check is ball achieved left or right edge
    checkIfScoreAchieved();

}

void Pong::render(DisplayProvider &display)
{
    if (resetScreenPending) {
        resetScreenPending = false;
        //display.fillScreen(getBackgroundColor());
        // display.displayGrassImage();
    }
    if(ballResetPending)
    {
        display.fillCircle(ballResetX, ballResetY, ball.getSize(), getBackgroundColor());
        ballResetPending = false;

    }
    if (stanGry == GAME_STOPPED) {
        display.setTextColor(TFT_WHITE, getBackgroundColor());
        display.drawString(countdown, 230, 100);
    }
    if (countdownClearPending) {
        display.fillRect(200, 90, 50, 50, getBackgroundColor());
        countdownClearPending = false;
    }

    platformLeft.draw(display);
    platformRight.draw(display);
    if (speed == maxSpeed) {
        ball.setColor(ballColor);
        ballColor += 50;
    }
    else {
        ball.setColor(0xffffff);
    }
    //ball.draw(display);
    //display.fillCircle(ball.getLastX(), ball.getLastY(), ball.getSize(), TFT_GREEN);
    display.displaySegmentedBg(segmentedBackground);
    display.displayBallImage(ball.getX()-10, ball.getY()+30-9);



}

void Pong::forceRender(DisplayProvider &display)
{

}

void Pong::end()
{

}

void Pong::handleRightPlatformMoveOnButtonsPressed()
{
    if(isButtonTopPressed)
    {
        platformRight.btnUpPressed();
    }

    if(isButtonBottomPressed)
    {
        platformRight.btnDownPressed();
    }
}

void Pong::updateOverlayText()
{
    overlayText = "";
#ifdef EMULATOR
    if(scoreLeft < 1000)
    {
        overlayText += "0";
    }
    if(scoreLeft < 100)
    {
        overlayText += "0";
    }
    if(scoreLeft < 10)
    {
        overlayText += "0";
    }
    overlayText += String(QString::number(scoreLeft));
    overlayText += " | ";


    if(scoreRight < 1000)
    {
        overlayText += "0";
    }
    if(scoreRight < 100)
    {
        overlayText += "0";
    }
    if(scoreRight < 10)
    {
        overlayText += "0";
    }
    overlayText += String(QString::number(scoreRight));
#else
    if(scoreLeft < 1000)
    {
        overlayText += "0";
    }
    if(scoreLeft < 100)
    {
        overlayText += "0";
    }
    if(scoreLeft < 10)
    {
        overlayText += "0";
    }
    overlayText += String(scoreLeft);
    overlayText += " | ";

    if(scoreRight < 1000)
    {
        overlayText += "0";
    }
    if(scoreRight < 100)
    {
        overlayText += "0";
    }
    if(scoreRight < 10)
    {
        overlayText += "0";
    }
    overlayText += String(scoreRight);
#endif

    PortableOS::activateAppTextMode(overlayText, 0x1070AD);

}

void Pong::randomizeBallDir()
{
    ball.setVelocity(Vector2D(0, 0));

    ball.move(237, 147);
    float dirX = 0.f, dirY;
    while (fabs(dirX) < 2.f) {
#ifdef EMULATOR
    dirX = rand()%40;
    dirY = rand()%40;
#else
    dirX = random(40);
    dirY = random(40);
#endif
    dirX -= 20;
    dirY -= 20;
    }
    Vector2D initDir(dirX, dirY);
    initDir = Vector2D::getNormalizedVector(initDir);
    ball.setAcceleration(speed);
    ball.applyMovementForce(initDir, speed);
}

String Pong::getAppNameString()
{
    return "Pong";
}

uint16_t Pong::getBackgroundColor()
{
    return TFT_BLACK;
}

void Pong::detectEdgeReflections()
{
    if (ball.getY() >= 280 || ball.getY() <= 10) {
        ball.reflectVelocityY();
    }


}

void Pong::detectBouncePlatformsReflection()
{
    if (platformRight.reflect(ball) || platformLeft.reflect(ball)) {
        if (speed <= maxSpeed) {
            speed += 0.4f;
            ball.setAcceleration(speed);
        }
    }
}

void Pong::gameReset()
{
    ballResetX = ball.getLastX();
    ballResetY = ball.getLastY();
    ballResetPending = true;
    stanGry = GAME_STOPPED;
    speed = 4.f;

    randomizeBallDir();



}

void Pong::checkIfScoreAchieved()
{
    if (ball.getX() >= (480 + ball.getSize())) {
        gameReset();
        scoreLeft++;
        updateOverlayText();
    }
    else if (ball.getX() <= (0 - ball.getSize())) {
        gameReset();
        scoreRight++;
        updateOverlayText();
    }

}

BouncePlatform::BouncePlatform(float x, float y, float w, float h, bool right): pos(x, y), width(w), height(h), isRight(right)
{

}

bool BouncePlatform::reflect(Character2D &character)
{
    Vector2D ballPos = character.getPosition();
    Vector2D reflectionForce = isRight ? Vector2D{-1, 0} : Vector2D{1, 0};
    bool isReflectedRetVal = false;
    if(isRight)
    {
        bool isBallInRightPlatformVerticalReflectionRange =
                (character.getY() >= getTopY() &&
                 character.getY() <= getBottomY()) ?
                    true : false;


        bool isBallInRightPlatformHorizontalReflectionRange =
                (character.getX() >= getReflectionX() &&
                 character.getX() <= getReflectionX() + getWidth()) ?
                    true : false;


        // Left edge collision
        if (isBallInRightPlatformVerticalReflectionRange) {

            Vector2D ballOnPlatformProjection =
                    Vector2D(getReflectionX(), ballPos.getY());
            Vector2D distanceToReflectionLine =
                    ballOnPlatformProjection - ballPos;

            if (distanceToReflectionLine.getLength() <= character.getSize()) {
                character.reflectVelocityX();
                isReflectedRetVal = true;
            }
        }

        // Top or bottom edge collision
        if(isBallInRightPlatformHorizontalReflectionRange)
        {
            Vector2D ballOnTopOfPlatformProjection =
                    Vector2D(ballPos.getX(), getTopY());
            Vector2D ballOnBottomOfPlatformProjection =
                    Vector2D(ballPos.getX(), getBottomY());
            Vector2D distanceToTopReflectionLine = ballOnTopOfPlatformProjection - ballPos;
            Vector2D distanceToBottomReflectionLine = ballOnBottomOfPlatformProjection - ballPos;

            if (distanceToTopReflectionLine.getLength() <= character.getSize()
                    || distanceToBottomReflectionLine.getLength() <= character.getSize()) {
                character.reflectVelocityY();
                isReflectedRetVal = true;
            }
        }
    } else
    {
        bool isBallInLeftPlatformVerticalReflectionRange =
                (character.getY() >= getTopY() &&
                 character.getY() <= getBottomY()) ?
                    true : false;


        bool isBallInLeftPlatformHorizontalReflectionRange =
                (character.getX() <= getReflectionX() &&
                 character.getX() >= getReflectionX() - getWidth()) ?
                    true : false;

        // Left edge collision
        if (isBallInLeftPlatformVerticalReflectionRange) {

            Vector2D ballOnPlatformProjection =
                    Vector2D(getReflectionX(), ballPos.getY());
            Vector2D distanceToReflectionLine =
                    ballOnPlatformProjection - ballPos;

            if (distanceToReflectionLine.getLength() <= character.getSize()) {
                character.reflectVelocityX();
                isReflectedRetVal = true;
            }
        }

        // Top or bottom edge collision
        if(isBallInLeftPlatformHorizontalReflectionRange)
        {
            Vector2D ballOnTopOfPlatformProjection =
                    Vector2D(ballPos.getX(), getTopY());
            Vector2D ballOnBottomOfPlatformProjection =
                    Vector2D(ballPos.getX(), getBottomY());
            Vector2D distanceToTopReflectionLine = ballOnTopOfPlatformProjection - ballPos;
            Vector2D distanceToBottomReflectionLine = ballOnBottomOfPlatformProjection - ballPos;

            if (distanceToTopReflectionLine.getLength() <= character.getSize()
                    || distanceToBottomReflectionLine.getLength() <= character.getSize()) {
                character.reflectVelocityY();
                isReflectedRetVal = true;
            }
        }
    }

    // Apply reflection force
    if (isReflectedRetVal && speed != 0) {
        if (speed > 0) {
            reflectionForce.setY(1);
        }
        else {
            reflectionForce.setY(-1);
        }
        character.applyMovementForce(reflectionForce, abs(speed)*0.01/0.5);
    }

    return isReflectedRetVal;
}

void BouncePlatform::draw(DisplayProvider &display)
{
    if (lastDiffChanged) {
        lastDiffChanged = false;
        display.fillRect(pos.getX(), lastPosDiff.getY(), width, abs(lastSpeed), TFT_BLACK);
    }
    display.fillRect(pos.getX(), pos.getY(), width, height, TFT_WHITE);
}

void BouncePlatform::moveUp(uint8_t pixels)
{
    lastSpeed = pixels + 1;
    float newYproposal = pos.getY() - pixels;
    if(newYproposal > 1) {
        lastDiffChanged = true;
        lastPosDiff.setY(pos.getY() + height - pixels);
        pos.setY(newYproposal);
    }
    else {
        if (pos.getY() != 1) {
            speed = 0;
            lastDiffChanged = true;
            lastPosDiff.setY(pos.getY() + height - pixels);
            pos.setY(1);
        }
    }
}

void BouncePlatform::moveDown(uint8_t pixels)
{
    lastSpeed = pixels;
    float newYproposal = pos.getY() + pixels;
    if (newYproposal < 300 - height) {
        lastDiffChanged = true;
        lastPosDiff.setY(pos.getY() - 1);
        pos.setY(pos.getY() + pixels);
    }
    else {
        if (pos.getY() != 300 - height) {
            speed = 0;
            lastDiffChanged = true;
            lastPosDiff.setY(pos.getY() - 1);
            pos.setY(300 - height);
        }
    }

}

void BouncePlatform::update()
{
    static uint8_t counter = 0;
    int absSpeed = abs(speed);
    if (speed > 0) {
        moveDown(speed);
    }
    else if (speed < 0) {
        moveUp(absSpeed);
    }

    if (pos.getY() == 1) {
        minYreached = true;
    }
    else {
        minYreached = false;
    }

    if (pos.getY() == 300 - height) {
        maxYreached = true;
    }
    else {
        maxYreached = false;
    }

    if (speed != 0 && !isBtnPressed && counter >= SPEED_INCREMENT_VAL) {
        counter = 0;
        if (speed > 0) {
            speed--;
        }
        else if (speed < 0) {
            speed++;
        }
    }
    isBtnPressed = false;
    counter++;
}

float BouncePlatform::getReflectionX()
{
    if(isRight) {
        return pos.getX();
    }
    else {
        return pos.getX() + width;
    }
}

float BouncePlatform::getTopY()
{
    return pos.getY();
}

float BouncePlatform::getBottomY()
{
    return pos.getY() + height;
}

float BouncePlatform::getHeight()
{
    return height;
}

float BouncePlatform::getWidth()
{
    return width;
}

void BouncePlatform::btnUpPressed()
{
    static uint8_t counter = 0;
    if (abs(speed) <= maxSpeedAbs && counter >= SPEED_INCREMENT_VAL && !minYreached) {
        counter = 0;
        speed -= 2;
    }
    isBtnPressed = true;
    counter++;
}

void BouncePlatform::btnDownPressed()
{
    static uint8_t counter = 0;
    if (abs(speed) <= maxSpeedAbs && counter >= SPEED_INCREMENT_VAL && !maxYreached) {
        counter = 0;
        speed += 2;
    }
    isBtnPressed = true;
    counter++;
}

PongLauncher::PongLauncher()
{
    pongMainMenu.registerChoiceDonePollValue((int8_t*)&selectionState);
}

PongLauncher::~PongLauncher()
{
    if(pongGamePtr != nullptr) {
        delete pongGamePtr;
    }
}

void PongLauncher::start(int w, int h)
{

}

void PongLauncher::input(InputType input)
{
    if(pongGamePtr == nullptr) {
        pongMainMenu.input(input);
    }
    else {
        pongGamePtr->input(input);
    }
}

void PongLauncher::longPressInput(InputType input)
{
    if (pongGamePtr != nullptr) {
        pongGamePtr->longPressInput(input);
    }
}

void PongLauncher::longPressRelease(InputType input)
{
    if (pongGamePtr != nullptr) {
        pongGamePtr->longPressRelease(input);
    }
}

void PongLauncher::analogInput(int x, int y)
{
    if(pongGamePtr == nullptr) {
        pongMainMenu.analogInput(x, y);
    }
    else {
        pongGamePtr->analogInput(x, y);
    }
}

void PongLauncher::touchInput(int x, int y)
{

}

void PongLauncher::update()
{
    switch (selectionState) {
    case NOT_SELECTED:
        pongMainMenu.update();
        break;
    case SINGLEPLAYER_SELECTED:
        if (pongGamePtr == nullptr) {
            pongGamePtr = new Pong(true);
            pongGamePtr->start(480, 290);
        }
    case DUEL_SELECTED:
        if (pongGamePtr == nullptr) {
            pongGamePtr = new Pong(true);
            pongGamePtr->start(480, 290);
        }
    case MULTIPLAYER_SELECTED:
        if (pongGamePtr == nullptr) {
            pongGamePtr = new Pong(true);
            pongGamePtr->start(480, 290);
        }
        pongGamePtr->update();
    default:
        break;
    }
}

void PongLauncher::render(DisplayProvider &display)
{
    if(pongGamePtr == nullptr) {
        pongMainMenu.render(display);
    }
    else {
        pongGamePtr->render(display);
    }

}

void PongLauncher::forceRender(DisplayProvider &display)
{
    if(pongGamePtr == nullptr) {
        pongMainMenu.render(display);
    }
    else {
        pongGamePtr->render(display);
    }

}

void PongLauncher::end()
{

}

String PongLauncher::getAppNameString()
{
    if (pongGamePtr == nullptr) {
        return "Pong";
    }
    return pongGamePtr->getAppNameString();
}

uint16_t PongLauncher::getBackgroundColor()
{
    if (pongGamePtr == nullptr) {
        return TFT_BLACK;
    }
    return pongGamePtr->getBackgroundColor();
}


void PongLauncher::udpDataReceived(int messageID, std::vector<uint8_t> data) {}