#include <app/tools/obstacle.hpp>
#include <app/tools/character2d.hpp>
#include "os/portableos.hpp"

Obstacle::Obstacle(float ax, float ay, int aw, int ah):x(ax), y(ay), type(Rectangle), w(aw), h(ah){
    if( w >= h)
    {
        isWgreatherThanH = true;
        forceRange = w/2 +12;
    }else
    {
        isWgreatherThanH = false;
        forceRange = h/2 + 12;
    }
}

Obstacle::Obstacle(float ax, float ay, int aradius):x(ax), y(ay), type(Circle), radius(aradius), forceRange(aradius * 2.f) {}

void Obstacle::draw(DisplayProvider& dispProvider) {
    switch(type) {
        case Rectangle:
            dispProvider.fillRect(x, y, w, h, TFT_ORANGE);
        break;
        case Circle:
            dispProvider.fillCircle(x, y, radius, TFT_ORANGE);
        break;
        default:
        break;
    }
}

bool Obstacle::isInCollision(float ax, float ay, int aradius) {
    switch(type) {
        case Rectangle:
            // return false;
            return isRectangleCollision(ax, ay, aradius);
        break;
        case Circle:
            Vector2D vecObjToObstacle(ax - x, ay - y);
            if (vecObjToObstacle.getLength() <= (radius + aradius)) {
                return true;
            }
            else {
                return false;
            }
        break;
    }
}

float Obstacle::getForceRange()
{
    return forceRange;
}

bool Obstacle::isRectangleCollision(float ax, float ay, int aradius) {
    DirectionType collidingLine = getCollidingRectangleLine(ax, ay);
    float distance = 0.f;
    int cornerCollisionRadiusReducer = 2; // px
    switch(collidingLine) {
        case Top:
            // Serial.println("top");
            distance = fabs(y - ay);
            // Serial.println("dis: " + String(distance));
            return ((ax <= x + w + (aradius - cornerCollisionRadiusReducer) ) && (ax >= x-(aradius - cornerCollisionRadiusReducer))) && (distance <= aradius);
        break;
        case Left:
            // Serial.println("left");
            distance = fabs(x - ax);
            return ((ay <= y + h + (aradius - cornerCollisionRadiusReducer) ) && (ay >= y - (aradius - cornerCollisionRadiusReducer))) && (distance <= aradius);
        break;
        case Right:
            // Serial.println("right");
            distance = fabs((x + w) - ax);
            return ((ay <= y + h + (aradius - cornerCollisionRadiusReducer)) && (ay >= y - (aradius - cornerCollisionRadiusReducer))) && (distance <= aradius);
        break;
        case Bottom:
            // Serial.println("bottom");
            distance = fabs((y + h) - ay);
            return ((ax <= x + w + (aradius - cornerCollisionRadiusReducer)) && (ax >= x - (aradius - cornerCollisionRadiusReducer))) && (distance <= aradius);
        break;
        default:
            return false;
        break;
    }
}

DirectionType Obstacle::getCollidingRectangleLine(float ax, float ay) {
    DirectionType retval = Top;
    if (y < ay && ay < (y + h)) {
        if (ax > (x + w)) {
            retval = Right;
        }
        else {
            retval = Left;
        }
    }
    else if (ay < y) {
        retval = Top;
    }
    else {
        retval = Bottom;
    }
    return retval;
}

Vector2D Obstacle::getPosition() {
    if(type == Rectangle)
    {
        return Vector2D(x+w/2, y+h/2);
    }
    else
    {
        return Vector2D(x, y);
    }
}

Vector2D Obstacle::getPushingForce(Character2D& character) {
    if(type == Circle) {
        return calculateForceForCircle(character);
    }else if(type == Rectangle)
    {
        return calculateForceForRectangle(character);
    }
    return Vector2D(0, 0);
}


Vector2D Obstacle::calculateForceForRectangle(Character2D& character)
{
    float middleX = x + (w / 2.f);
    float middleY = y + (h / 2.f);

    //PortableOS::display.fillCircle(middleX, middleY, forceRange, TFT_WHITE);

    Vector2D middleAsVec2D(middleX, middleY);

    Vector2D obstacleToEnemyVector = (character.getPosition() - middleAsVec2D);
    //calculate vector length
    float distanceBetween = obstacleToEnemyVector.getLength();
    if (distanceBetween <= forceRange) {
        //calculate force value
        float force = (distanceBetween/forceRange);
        //get force direction vector
        Vector2D forceVector = Vector2D::getNormalizedVector(obstacleToEnemyVector);
        //apply force
        forceVector.rescale(force);

        PortableOS::display.drawLine(middleX, middleY, 
            middleX+obstacleToEnemyVector.getX(), 
            middleY+obstacleToEnemyVector.getY(), 
            0x0002ff
            );


        return forceVector;
    }
    else {
        //return 0 - forceVector
        //character is too far
        return Vector2D(0, 0);
    }

    return Vector2D(0, 0);
}

Vector2D Obstacle::calculateForceForCircle(Character2D& character)
{
    //PortableOS::display.fillCircle(x, y, forceRange, TFT_WHITE);

    //find vector between enemy and obstacle
    Vector2D obstacleToEnemyVector = (character.getPosition() - getPosition());
    //calculate vector length
    float distanceBetween = obstacleToEnemyVector.getLength();

    //if character is in range of pushing force
    if (distanceBetween <= forceRange) {
        //calculate force value
        float force = (distanceBetween/forceRange);
        //get force direction vector
        Vector2D forceVector = Vector2D::getNormalizedVector(obstacleToEnemyVector);
        //apply force
        forceVector.rescale(force);

        PortableOS::display.drawLine(x, y, 
            x+obstacleToEnemyVector.getX(), 
            y+obstacleToEnemyVector.getY(), 
            0x0002ff
            );
        

        return forceVector;
    }
    else {
        //return 0 - forceVector
        //character is too far
        return Vector2D(0, 0);
    }
}
