#include "vector2D.h"

Vector2D::Vector2D(u16 X, u16 Y) {
    x = X;
    y = Y;
}

// Makes it possible to add xyPairs directly
Vector2D Vector2D::operator + (Vector2D param) {
    Vector2D temp;
    temp.x = x + param.x;
    temp.y = y + param.y;
    return (temp);
}

Vector2D& Vector2D::operator += (Vector2D param) {
    x += param.x;
    y += param.y;
    return *this;
}

void Vector2D::clear() {
    x = 0;
    y = 0;
}
