#include "app/tools/vector2d.hpp"

Vector2D::Vector2D(float ax, float ay): x(ax), y(ay) {

}

float Vector2D::getX() const{
    return x;
}

float Vector2D::getY() const{
    return y;
}

float Vector2D::getLength() const{
    return sqrt(((x * x) + (y * y)));
}

Vector2D Vector2D::operator-(const Vector2D& obj) {
    Vector2D temp(this->getX() - obj.getX(), this->getY() - obj.getY());
    return temp;
}

Vector2D Vector2D::operator+(const Vector2D& obj) {
    Vector2D temp(this->getX() + obj.getX(), this->getY() + obj.getY());
    return temp;
}

void Vector2D::rescale(float factor) {
//    float tempX = this->getX(), tempY = this->getY();

//    if (tempX < 0) {
//        this->x *= factor;
//    }
//    else if (tempX > 0) {
//        this->x *= factor;
//    }
//    if (tempY < 0) {
//        this->y *= factor;
//    }
//    else if (tempY > 0) {
//        this->y *= factor;
//    }
    x *= factor;
    y *= factor;
}

Vector2D Vector2D::operator*(float factor) {
    Vector2D temp(this->getX() * factor, this->getY() * factor);
    return temp;
}

void Vector2D::setX(float ax) {
    x = ax;
}

void Vector2D::setY(float ay) {
    y = ay;
}

void Vector2D::set(float ax, float ay) {
    setX(ax);
    setY(ay);
}

Vector2D Vector2D::getNormalizedVector(Vector2D& vec) {
    float length = vec.getLength();
    return Vector2D((vec.getX() / length), (vec.getY() / length));
}
