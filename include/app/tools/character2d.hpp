#ifndef CHARACTER2D_H
#define CHARACTER2D_H
#include "targetDatatypes.hpp"
#include "os/displayprovider.hpp"
#include "app/tools/vector2d.hpp"
#include "app/tools/obstacle.hpp"
#include <vector>

typedef enum {
    Chasing_Player,
    Avoiding_Obstacle
}EnemyMoveAlgorithm;


typedef struct
{
    float startX;
    float startY;
    float width;
    float height;
}SquareMoveLimitArea;

class Character2D 
{
    static unsigned idGlobalCounter;
    unsigned id;
    Vector2D position;
    Vector2D velocityDirection;
    float minX = 0.f, minY = 0.f, maxX = 480.f, maxY = 320.f;
    std::vector<SquareMoveLimitArea> squareMoveLimitAreas;
    float acceleration = 0.5f;
    Vector2D lastPosition;
    uint8_t size;
    Obstacle* avoidedObj = nullptr;
    EnemyMoveAlgorithm moveAlgorithm = Chasing_Player;
    bool isEnemy = true;
    bool killed = false;
    uint32_t color = TFT_RED;
    uint32_t bgcolor = TFT_BLACK;

    void updatePlayerCoordinates(float x, float y);

    public:
    Character2D(float ax, float ay, uint8_t asize);
    void update();
    void draw(DisplayProvider& display);
    void kill();
    bool isKilled();
    unsigned getId();
    void applyMovementForce(Vector2D& force, float forceAcceleration);
    void move(float ax, float ay);
    void moveBy(float ax, float ay);
    float getX();
    float getY();
    Vector2D getPosition();
    float getAcceleration();
    void setAcceleration(float aSpeedFactor);
    uint8_t getSize();
    void setCharacterMoveRanges(float aminX, float aminY, float amaxX, float amaxY);
    float getLastX();
    float getLastY();

    void setLastXandY(float ax, float ay);
    void setColor(uint32_t acolor);
    void setBgColor(uint32_t abgcolor);


    Vector2D getVelocity();
    void setVelocity(Vector2D aVelocity);

    void reflectVelocityX();
    void reflectVelocityY();


    void setNewSquareMoveLimitAreas(std::vector<SquareMoveLimitArea>& vec);
    void clearSquareMoveLimitAreas();

};

#endif
