#include "app/games/ZombieBattle.hpp"

ZombieBattle::ZombieBattle()
{
}

void ZombieBattle::start(int w, int h)
{
    gun.rotate(40);
    Vector2D pos(350, groundLevelY);
    zombies.push_back({pos});
}

void ZombieBattle::input(InputType input)
{
    if (input == BUTTON_A)
    {
        gun.shot();
    }
}

void ZombieBattle::udpDataReceived(int messageID, std::vector<uint8_t> data)
{
}

void ZombieBattle::longPressInput(InputType input)
{
}

void ZombieBattle::longPressRelease(InputType input)
{
}

void ZombieBattle::analogInput(int x, int y)
{
    // if(x != 0 || y != 0)
    // {
    //     Serial.println(String(x) + " " + String(y));
    // }

    int absoluteForce = abs(y);
    int angle = 0;
    if (absoluteForce >= 5)
    {
        angle = 1;
    }
    else if (absoluteForce >= 7)
    {
        angle = 2;
    }
    else if (absoluteForce == 10)
    {
        angle = 3;
    }

    if (y >= 5)
    {
        gun.rotate(-angle);
    }
    else if (y <= -5)
    {
        gun.rotate(angle);
    }
}

void ZombieBattle::touchInput(int x, int y)
{
}

void ZombieBattle::update()
{
    for (auto &shot : gun.getShots())
    {
        shot.update();
    }

    for (auto &zombie : zombies)
    {
        zombie.update();
    }
    updateShotsCollisions();
}

void ZombieBattle::render(DisplayProvider &display)
{
    renderBG(display);
    gun.render(display);
    renderPlayer(display);
    for (auto &shot : gun.getShots())
    {
        shot.draw(display, TFT_BLACK, TFT_YELLOW);
    }

    gun.getShots().erase(std::remove_if(gun.getShots().begin(),
                                        gun.getShots().end(),
                                        [](GunShot &element)
                                        { return element.destroyed(); }),
                         gun.getShots().end());

    for (auto &zombie : zombies)
    {
        zombie.draw(display, TFT_YELLOW);
    }
}

void ZombieBattle::renderBG(DisplayProvider &display)
{
    if (flags.needDrawBG == true)
    {
        display.fillRect(0, groundLevelY, 480, 50, TFT_BROWN);
        display.fillRect(0, groundLevelY - 150, 60, 150, TFT_ORANGE);
        // display.drawLine(60,,70,,TFT_GREENYELLOW);
        flags.needDrawBG = false;
    }
}

void ZombieBattle::renderPlayer(DisplayProvider &display)
{
    display.fillCircle(40, groundLevelY - 150, 30, TFT_CYAN);
}

void ZombieBattle::forceRender(DisplayProvider &display)
{
}

void ZombieBattle::end()
{
}

String ZombieBattle::getAppNameString()
{
    return "ZombieBattle";
}

uint16_t ZombieBattle::getBackgroundColor()
{
    return TFT_YELLOW;
}

Point2D::Point2D(int ax, int ay)
{
    x = ax;
    y = ay;
}

RotatingGun::RotatingGun(Point2D pos, int rot)
{
    position = pos;
    rotation = rot;

    defaultPoints.push_back(pos);
    defaultPoints.push_back({pos.x + 15, pos.y - 2});
    defaultPoints.push_back({pos.x + 18, pos.y - 7});
    defaultPoints.push_back({pos.x - 4, pos.y - 7});
    defaultPoints.push_back({pos.x - 4, pos.y + 10});
    defaultPoints.push_back({pos.x - 1, pos.y + 10});

    gunPoints = defaultPoints;
}

void RotatingGun::render(DisplayProvider &display)
{
    if (!wasRotation)
    {
        return;
    }
    wasRotation = false;

    if (!lastRenderGunPoints.empty())
    {
        for (int i = 1; i < lastRenderGunPoints.size(); i++)
        {
            display.drawLine(lastRenderGunPoints.at(i - 1).x, lastRenderGunPoints.at(i - 1).y, lastRenderGunPoints.at(i).x, lastRenderGunPoints.at(i).y, TFT_YELLOW);
        }
        display.drawLine(lastRenderGunPoints.at(lastRenderGunPoints.size() - 1).x, lastRenderGunPoints.at(lastRenderGunPoints.size() - 1).y, lastRenderGunPoints.at(0).x, lastRenderGunPoints.at(0).y, TFT_YELLOW);
    }

    for (int i = 1; i < gunPoints.size(); i++)
    {
        display.drawLine(gunPoints.at(i - 1).x, gunPoints.at(i - 1).y, gunPoints.at(i).x, gunPoints.at(i).y, TFT_BLACK);
    }
    display.drawLine(gunPoints.at(gunPoints.size() - 1).x, gunPoints.at(gunPoints.size() - 1).y, gunPoints.at(0).x, gunPoints.at(0).y, TFT_BLACK);
    lastRenderGunPoints = gunPoints;
}

void RotatingGun::rotate(float angle)
{
    int finalAngle = rotation + angle;

    if (finalAngle < -80 || finalAngle > 80)
    {
        return;
    }

    gunPoints = defaultPoints;

    double angleRad = finalAngle * M_PI / 180.0;

    double cosA = std::cos(angleRad);
    double sinA = std::sin(angleRad);

    for (auto &p : gunPoints)
    {
        double x = (double)p.x - (double)position.x;
        double y = (double)p.y - (double)position.y;

        double xNew = x * cosA - y * sinA;
        double yNew = x * sinA + y * cosA;

        p.x = (int)xNew + position.x;
        p.y = (int)yNew + position.y;
    }
    rotation = finalAngle;
    wasRotation = true;

    getBasisDegrees();
    // Move up
    shotPos.x = position.x - ((int)((up.getX() * 100)) / 14);
    shotPos.y = position.y - ((int)((up.getY() * 100)) / 14);

    // Move to the right
    shotPos.x += ((int)((right.getX() * 100)) / 4);
    shotPos.y += ((int)((right.getY() * 100)) / 4);
}

int RotatingGun::getRotation()
{
    return rotation;
}

void RotatingGun::getBasisDegrees()
{
    double angleRad = rotation * M_PI / 180.0;

    double cosA = std::cos(angleRad);
    double sinA = std::sin(angleRad);

    right = {(float)cosA, (float)sinA};
    up = {(float)-sinA, (float)cosA};
}

void RotatingGun::shot()
{
    Vector2D pos{shotPos.x, shotPos.y};
    gunShots.push_back({pos, right, 230, 60});
    // Serial.println("Shot at angle: " + String(rotation) + " with right vector: " + String(right.getX()) + " " + String(right.getY()) + " and up vector: " + String(up.getX()) + " " + String(up.getY()));
    // Serial.println("Shot position: " + String(shotPos.x) + " " + String(shotPos.y));
}

std::vector<GunShot> &RotatingGun::getShots()
{
    return gunShots;
}

void ZombieBattle::updateShotsCollisions()
{
    for (auto &shot : gun.getShots())
    {
        for (auto &zombie : zombies)
        {
            Vector2D l(shot.getPos().getX() - zombie.getPos().getX(), shot.getPos().getY() - zombie.getPos().getY());

            if(l.getLength() <= (2 + 30))
            {
                zombie.hit(20);
                shot.destroy();
            }
        }
    }
}