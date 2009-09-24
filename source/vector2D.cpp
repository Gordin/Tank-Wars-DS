#include "vector2D.h"

Vector2D::Vector2D(s32 X, s32 Y) {
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

Vector2D Vector2D::operator - (Vector2D param) {
    Vector2D temp;
    temp.x = x + param.x;
    temp.y = y + param.y;
    return (temp);
}

Vector2D Vector2D::operator / (int param) {
    Vector2D temp;
    temp.x = x / param;
    temp.y = y / param;
    return (temp);
}

Vector2D& Vector2D::operator += (Vector2D param) {
    x += param.x;
    y += param.y;
    return *this;
}

Vector2D Vector2D::operator >> (int param) {
    Vector2D temp;
    temp.x = x >> param;
    temp.y = y >> param;
    return *this;
}

Vector2D Vector2D::operator << (int param) {
    Vector2D temp;
    temp.x = x << param;
    temp.y = y << param;
    return *this;
}

void Vector2D::clear() {
    x = 0;
    y = 0;
}
