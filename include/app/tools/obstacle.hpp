#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "os/displayprovider.hpp"
#include "app/tools/vector2d.hpp"

typedef enum{
    Rectangle,
    Circle
}ObstacleType;

typedef enum{
    Top,
    Bottom,
    Right,
    Left
}DirectionType;

class Character2D;

class Obstacle
{
    float x, y;
    ObstacleType type;
    int w, h;
    bool isWgreatherThanH = false;
    int radius;
    float forceRange;
    bool isRectangleCollision(float ax, float ay, int aradius);
    DirectionType getCollidingRectangleLine(float ax, float ay);
    Vector2D calculateForceForRectangle(Character2D& character);
    Vector2D calculateForceForCircle(Character2D& character);



    public:
    Obstacle(float ax, float ay, int aw, int ah);
    Obstacle(float ax, float ay, int aradius);
    void draw(DisplayProvider& dispProvider);
    bool isInCollision(float ax, float ay, int aradius);
    float getForceRange();
    Vector2D getPosition();
    Vector2D getPushingForce(Character2D& character);
};

#endif
