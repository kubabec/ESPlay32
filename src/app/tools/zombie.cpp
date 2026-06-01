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
    // display.fillCircle(lastPos.getX(), lastPos.getY(), 2, bgColor);
    // display.fillCircle(pos.getX(), pos.getY(), 2, 0xFFFFFF);

    renderZombie(display,bgColor);
}
void Zombie::renderZombie(DisplayProvider &display, uint16_t bgColor)
{

    display.fillRect(lastPos.getX(),lastPos.getY() - 30, 30, 30, bgColor);
    display.fillRect(lastPos.getX(),lastPos.getY(), 30, 30, TFT_BROWN);
    display.fillCircle(pos.getX(), pos.getY(), 30, TFT_GREEN);
    display.drawLine(pos.getX() - 55, pos.getY() ,pos.getX() + 10,pos.getY() - 10,TFT_GREEN);
    display.drawLine(pos.getX() - 55, pos.getY() - 10,pos.getX(),pos.getY() - 15,TFT_GREEN);

}
Vector2D Zombie::getPos()
{
    return pos;
}
