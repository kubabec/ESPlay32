#include "app/tools/zombie.h"

Zombie::Zombie(Vector2D &apos) : pos(apos)
{
}

void Zombie::update()
{
    lastPos = pos;
    Vector2D posPrim = pos + (Vector2D(-1, 0) * acceleration);
    pos = posPrim;
}

void Zombie::draw(DisplayProvider &display, uint16_t bgColor)
{
    display.fillCircle(lastPos.getX(), lastPos.getY(), 2, bgColor);
    display.fillCircle(pos.getX(), pos.getY(), 2, 0xFFFFFF);

    renderZombie(display);
}
void Zombie::renderZombie(DisplayProvider &display)
{
    int groundLevelY = 240;

    display.fillCircle(280, groundLevelY, 30, TFT_DARKGREEN);
    display.drawLine(225, groundLevelY ,290,groundLevelY - 10,TFT_DARKGREEN);
    display.drawLine(225, groundLevelY - 10,280,groundLevelY - 15,TFT_DARKGREEN);

}
Vector2D Zombie::getPos()
{
    return pos;
}
