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

    renderZombie(display, bgColor);
}
void Zombie::renderZombie(DisplayProvider &display, uint16_t bgColor)
{

    static int clearCounter = 0;

    if (clearCounter < 10)
    {
        clearCounter++;
    }

    if (clearCounter >= 10)
    {
        clearCounter = 0;
        display.fillRect(lastPos.getX(), lastPos.getY() - 30, 60, 30, bgColor);
        display.fillRect(lastPos.getX(), lastPos.getY(), 60, 35, TFT_BROWN);
    }

    if (!isDead())
    {
        grey(display);
    }
    else
    {
        display.fillRect(lastPos.getX(), lastPos.getY() - 30, 60, 30, bgColor);
        display.fillRect(lastPos.getX(), lastPos.getY(), 60, 35, TFT_BROWN);
    }
}
Vector2D Zombie::getPos()
{
    return pos;
}

int Zombie::hit(int damage)
{
    hp = hp - damage;
    if (hp < 0)
    {
        hp = 0;
    }

    return hp;
}

void Zombie::grey(DisplayProvider &display)
{

    uint32_t bodyColor = TFT_GREEN;

    
    if (hp <= 20)
    {
        bodyColor = TFT_BLACK;
    }

    else if (hp <= 40)
    {
        bodyColor = TFT_DARKGREY;
    }

    else if (hp <= 60)
    {
        bodyColor = TFT_LIGHTGREY;
    }

    else if (hp <= 80)
    {
        bodyColor = TFT_DARKGREEN;
    }

    display.fillCircle(pos.getX(), pos.getY(), 30, bodyColor);

    display.drawLine(pos.getX() - 55, pos.getY(), pos.getX() + 10, pos.getY() - 10, bodyColor);
    display.drawLine(pos.getX() - 55, pos.getY() - 10, pos.getX(), pos.getY() - 15, bodyColor);

    display.setTextColor(TFT_RED, bodyColor);
    display.setTextSize(1);
    display.drawString(String(hp), pos.getX() - 20, pos.getY() - 10);
}

bool Zombie::isDead()
{
    if (hp <= 0)
    {
        return true;
    }

    return false;
}