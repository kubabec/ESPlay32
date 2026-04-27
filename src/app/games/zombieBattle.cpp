#include "app/games/ZombieBattle.hpp"

ZombieBattle::ZombieBattle()
{
}

void ZombieBattle::start(int w, int h)
{
}

void ZombieBattle::input(InputType input)
{
}

void ZombieBattle::udpDataReceived(int messageID, std::vector<uint8_t> data)
{
}

void ZombieBattle::longPressInput(InputType input)
{
}

void ZombieBattle::longPressRelease(InputType input)
{
}

void ZombieBattle::analogInput(int x, int y)
{
}

void ZombieBattle::touchInput(int x, int y)
{
}

void ZombieBattle::update()
{
}

void ZombieBattle::render(DisplayProvider &display)
{
    renderBG(display);
    gun.render(display);
}

void ZombieBattle::renderBG(DisplayProvider &display)
{
    if (flags.needDrawBG == true)
    {
        display.fillRect(0, groundLevelY, 480, 50, TFT_BROWN);
        display.fillRect(0, groundLevelY - 150, 60, 150, TFT_ORANGE);
        // display.drawLine(60,,70,,TFT_GREENYELLOW);
        flags.needDrawBG = false;
    }
}

void ZombieBattle::forceRender(DisplayProvider &display)
{
}

void ZombieBattle::end()
{
}

String ZombieBattle::getAppNameString()
{
    return "ZombieBattle";
}

uint16_t ZombieBattle::getBackgroundColor()
{
    return TFT_YELLOW;
}

Point2D::Point2D(int ax, int ay)
{
    x = ax;
    y = ay;
}

RotatingGun::RotatingGun(Point2D pos, int rot)
{
    position = pos;
    rotation = rot;

    gunPoints.push_back(pos);
    gunPoints.push_back({pos.x + 15, pos.y - 2});
    gunPoints.push_back({pos.x + 18, pos.y - 7});
    gunPoints.push_back({pos.x - 4, pos.y - 7});
    gunPoints.push_back({pos.x - 4, pos.y + 10});
    gunPoints.push_back({pos.x - 1, pos.y + 10});
}

void RotatingGun::render(DisplayProvider &display)
{
    for (int i = 1; i < gunPoints.size(); i++)
    {
        display.drawLine(gunPoints.at(i - 1).x, gunPoints.at(i - 1).y, gunPoints.at(i).x, gunPoints.at(i).y, TFT_BLACK);
    }
    display.drawLine(gunPoints.at(gunPoints.size() - 1).x, gunPoints.at(gunPoints.size() - 1).y, gunPoints.at(0).x, gunPoints.at(0).y, TFT_BLACK);
}
