#include "app/tools/character2d.hpp"

unsigned Character2D::idGlobalCounter = 0;

Character2D::Character2D(float ax, float ay, uint8_t asize): position(ax, ay), lastPosition(ax, ay), size(asize)
{
    id = idGlobalCounter;
    idGlobalCounter++;
    velocityDirection = Vector2D(-1, 0);
    velocityDirection = Vector2D(velocityDirection);
}

void Character2D::update()
{
    moveBy(
            velocityDirection.getX()*acceleration,
            velocityDirection.getY()*acceleration
                );
}

void Character2D::draw(DisplayProvider &display)
{
    if(isEnemy){
        if(!killed){
        display.fillCircle(getLastX(), getLastY(), getSize(), bgcolor);
        //delay(3);
        display.fillCircle(getX(), getY(), getSize(), color);
        // Keep last rendered X and Y for each enemy
        setLastXandY(getX(), getY());
        }
        else
        {
            // clean screen from killed enemy
            display.fillCircle(getLastX(), getLastY(), getSize(), bgcolor);
            display.fillCircle(getX(), getX(), getSize(), bgcolor);
        }
    }
}

void Character2D::kill()
{
    killed = true;
}

bool Character2D::isKilled()
{
    return killed;
}

unsigned int Character2D::getId()
{
    return id;
}

void Character2D::applyMovementForce(Vector2D &force, float forceAcceleration)
{
    Vector2D vPrim(0,0);

    vPrim = velocityDirection + (force * forceAcceleration);

    velocityDirection = Vector2D::getNormalizedVector(vPrim);
}

void Character2D::move(float ax, float ay) {
    updatePlayerCoordinates(ax, ay);
}

void Character2D::moveBy(float ax, float ay) {
    updatePlayerCoordinates(position.getX() + ax, position.getY() + ay);
}

float Character2D::getX() {
    return position.getX();
}

float Character2D::getY() {
    return position.getY();
}

float Character2D::getAcceleration() {
    return acceleration;
}

Vector2D Character2D::getPosition() {
    return position;
}

void Character2D::setAcceleration(float aSpeedFactor) {
    acceleration = aSpeedFactor;
}

uint8_t Character2D::getSize() {
    return size;
}

void Character2D::setCharacterMoveRanges(float aminX, float aminY, float amaxX, float amaxY) {
    minX = aminX;
    minY = aminY;
    maxX = amaxX;
    maxY = amaxY;
}

float Character2D::getLastX() {
    return lastPosition.getX();
}

float Character2D::getLastY() {
    return lastPosition.getY();
}

Vector2D Character2D::getVelocity()
{
    return velocityDirection;
}

void Character2D::setVelocity(Vector2D aVelocity)
{
    velocityDirection = aVelocity;
}

void Character2D::reflectVelocityX()
{
    velocityDirection.setX(velocityDirection.getX() * -1.f);
}

void Character2D::reflectVelocityY()
{
    velocityDirection.setY(velocityDirection.getY() * -1.f);
}

void Character2D::setNewSquareMoveLimitAreas(std::vector<SquareMoveLimitArea>& vec)
{
    squareMoveLimitAreas = vec;
}

void Character2D::clearSquareMoveLimitAreas()
{
    squareMoveLimitAreas.clear();
}

void Character2D::updatePlayerCoordinates(float ax, float ay) {
    if (ay < size+minY) {
        ay = size+minY;
    }
    if (ay > maxY-size) {
        ay = maxY-size;
    }
    if (ax < size+minX) {
        ax = size+minX;
    }
    if (ax > maxX-size) {
        ax = maxX-size;
    }

    // Check move limit areas
    if(!squareMoveLimitAreas.empty())
    {
        for(auto& limitArea : squareMoveLimitAreas)
        {
            if(ax >= limitArea.startX && ax <= limitArea.startX + limitArea.width)
            {
                // Crosses top of the limit area
                if(fabs(ay - limitArea.startY) < size)
                {
                    ay = limitArea.startY - size;
                }else // Crosses bottom
                    if(fabs(ay - (limitArea.startY+limitArea.height)) < size)
                {
                    ay = limitArea.startY+limitArea.height + size;
                }
            }

            if(ay >= limitArea.startY && ay <= limitArea.startY + limitArea.height)
            {
                // Crosses left of the limit area
                if(fabs(ax - limitArea.startX) < size)
                {
                    ax = limitArea.startX - size;
                }else  // Crosses right
                    if(fabs(ax - (limitArea.startX+limitArea.width)) < size)
                {
                    ax = limitArea.startX+limitArea.width + size;
                }
            }
        }
    }

    lastPosition = position;
    position.setX(ax);

    position.setY(ay);
}

void Character2D::setLastXandY(float ax, float ay)
{
    lastPosition.setX(ax);
    lastPosition.setY(ay);
}

void Character2D::setColor(uint32_t acolor)
{
    color = acolor;
}

void Character2D::setBgColor(uint32_t abgcolor)
{
    bgcolor = abgcolor;
}
