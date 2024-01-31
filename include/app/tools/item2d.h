#ifndef ITEM2D_H
#define ITEM2D_H
#include <app/tools/character2d.hpp>
#include <os/displayprovider.hpp>

typedef enum {
    FOOD,
    INVISIBILITY_POTION,
    POTATO,
    NO_ATTACK_POTION,
    BLACK_HOLE,
    AMO_PACK
}GameItemType;

class Item2D
{
public:
    Item2D(float ax, float ay, GameItemType atype);
    bool isInCollision(Character2D& player);
    void draw(DisplayProvider& display);
    GameItemType getType();
    bool getRemoveFlag();
    void moveBy(int ax, int ay);
private:
    float x = 0, y = 0;
    GameItemType type;
    uint8_t size = 6;
    bool toBeRemoved = false;
};

#endif // ITEM2D_H
