#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <math.h>

class Vector2D {
    float x = 0.f, y = 0.f;
    public:
    Vector2D(float ax, float ay);
    Vector2D() = default;
    static Vector2D getNormalizedVector(Vector2D& vec);
    float getX() const;
    float getY() const;
    float getLength() const;
    void setX(float ax);
    void setY(float ay);
    void set(float ax, float ay);
    Vector2D operator-(const Vector2D& obj);
    Vector2D operator+(const Vector2D& obj);
    void rescale(float factor);
    Vector2D operator*(float factor);
};

#endif
