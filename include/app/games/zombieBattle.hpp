#ifndef ZOMBIEBATTLE_H
#define ZOMBIEBATTLE_H
#include "app/runtimeApplication.hpp"
#include <array>
#include "app/tools/gunshot.h"
#include "app/tools/zombie.h"


struct ZombieBattleFlags
{
    bool needDrawBG = true;
};

class Point2D
{
public:
    Point2D(int ax, int ay);

    int x;
    int y;
};


class RotatingGun
{
public:
    RotatingGun(Point2D pos, int rot);
    void render(DisplayProvider &display);
    void rotate(float angle);
    int getRotation();
    void shot();
    std::vector<GunShot>& getShots();

private:
    std::vector<Point2D> gunPoints;
    std::vector<Point2D> lastRenderGunPoints;
    std::vector<Point2D> defaultPoints;
    Point2D position{0,0};
    int rotation;
    bool wasRotation = true;
    Vector2D right;
    Vector2D up;
    Point2D shotPos{0,0};
    std::vector<GunShot> gunShots;

    void getBasisDegrees();
};


class ZombieBattle : public RuntimeApplication
{
public:
    ZombieBattle();
    virtual void start(int w, int h) override;
    virtual void input(InputType input) override;
    virtual void longPressInput(InputType input) override;
    virtual void longPressRelease(InputType input) override;
    virtual void analogInput(int x, int y) override;
    virtual void touchInput(int x, int y) override;
    virtual void update() override;
    virtual void render(DisplayProvider &display) override;
    virtual void forceRender(DisplayProvider &display) override;
    virtual void end() override;
    virtual String getAppNameString() override;
    virtual uint16_t getBackgroundColor() override;
    void udpDataReceived(int messageID, std::vector<uint8_t> data);

private:
    ZombieBattleFlags flags;
    const int groundLevelY = 240;
    RotatingGun gun{{100,100},0};
    std::vector<Zombie> zombies;
    unsigned long lastSpawnTime = 0;
    int score = 0;

    void renderBG(DisplayProvider &display);
    void renderPlayer(DisplayProvider &display);
    void updateShotsCollisions();
    void spawnZombie();

};

#endif