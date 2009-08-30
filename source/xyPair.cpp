#include "xyPair.h"

xyPair::xyPair(u16 X, u16 Y) {
    x = X;
    y = Y;
}

// Makes it possible to add xyPairs directly
xyPair xyPair::operator + (xyPair param) {
    xyPair temp;
    temp.x = x + param.x;
    temp.y = y + param.y;
    return (temp);
}

xyPair& xyPair::operator += (xyPair param) {
    x += param.x;
    y += param.y;
    return *this;
}

void xyPair::clear() {
    x = 0;
    y = 0;
}
