#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "app/tools/vector2d.hpp"
#include "os/displayprovider.hpp"

class Zombie
{
    Vector2D lastPos{0.f,0.f};
    Vector2D pos;
    float acceleration = 0.5f;
    int hp = 100;

public:
    Zombie(Vector2D& apos);

    void update();
    void draw(DisplayProvider& display,uint16_t bgColor);
    Vector2D getPos();
    void renderZombie(DisplayProvider &display, uint16_t bgColor);
    int hit(int damage);

};

#endif // GUNSHOT_H
