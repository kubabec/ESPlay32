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
}

Vector2D Zombie::getPos()
{
    return pos;
}
