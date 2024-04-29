#ifndef GUNSHOT_H
#define GUNSHOT_H
#include "app/tools/vector2d.hpp"
#include "os/displayprovider.hpp"

class GunShot
{
    Vector2D lastPos{0.f,0.f};
    Vector2D pos;
    Vector2D dir;
    uint16_t ttl;
    float acceleration = 3.f;
    int minY = 2;
    bool isDestroyed = false;
public:
    GunShot(Vector2D& apos, Vector2D& ashotDir, uint16_t attl = 30);

    void update();
    void draw(DisplayProvider& display);
    bool destroyed();
    void destroy();
    Vector2D getPos();

};

#endif // GUNSHOT_H
