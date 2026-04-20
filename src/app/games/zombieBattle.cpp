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
}

void ZombieBattle::renderBG(DisplayProvider &display)
{
    if (flags.needDrawBG == true)
    {
        display.fillRect(0, groundLevelY, 480, 50, TFT_BROWN);
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
