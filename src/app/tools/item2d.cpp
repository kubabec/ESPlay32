#include "app/tools/item2d.h"

Item2D::Item2D(float ax, float ay, GameItemType atype) :x(ax), y(ay), type(atype)
{

}

bool Item2D::isInCollision(Character2D &player)
{
    Vector2D vecObjToObstacle(player.getX() - x, player.getY() - y);
    if (vecObjToObstacle.getLength() <= ((size + player.getSize()) / 2)) {
        toBeRemoved = true;
        return true;
    }
    else {
        return false;
    }
}

void Item2D::draw(DisplayProvider &display)
{
    if(!toBeRemoved){
        uint32_t bgcolor = 0x0033aa;
        switch (type) {
            case FOOD:
                bgcolor = 0xcd5916;
            break;
            case INVISIBILITY_POTION:
                bgcolor = 0x62d3ed;
            break;
            case POTATO:
                bgcolor = 0xebb91d;
            break;
            case NO_ATTACK_POTION:
                bgcolor = 0xd0e0e3;
            break;
            case BLACK_HOLE:
                bgcolor = 0x363636;
            break;
            case AMO_PACK:
                bgcolor = 0xFFFFFF;
            break;
        }

        if(type != AMO_PACK)
        {
            display.fillCircle(x, y, size, bgcolor);
            display.drawLine(x - size, y, x + size, y, 0x000000);
            display.drawLine(x, y - size, x, y + size, 0x000000);
        }else
        {
            // AMO PACK shape
            display.fillCircle(x, y, 3, bgcolor);
            display.fillCircle(x, y+2, 3, bgcolor);
            display.fillCircle(x-2, y-3, 3, bgcolor);
            display.fillCircle(x+2, y-1, 2, bgcolor);
            display.fillCircle(x+3, y+2, 3, bgcolor);
        }
    }
    else {
        // Clean screen from removed item
        if(type != AMO_PACK)
        {
            display.fillCircle(x, y, size, TFT_BLACK);
        }else
        {
            // AMO PACK shape
            display.fillCircle(x, y, 3, TFT_BLACK);
            display.fillCircle(x, y+2, 3, TFT_BLACK);
            display.fillCircle(x-2, y-3, 3, TFT_BLACK);
            display.fillCircle(x+2, y-1, 2, TFT_BLACK);
            display.fillCircle(x+3, y+2, 3, TFT_BLACK);
        }

    }

}

GameItemType Item2D::getType()
{
    return type;
}

bool Item2D::getRemoveFlag()
{
    return toBeRemoved;
}

void Item2D::moveBy(int ax, int ay)
{
    x = x + ax;
    y = y + ay;
}
