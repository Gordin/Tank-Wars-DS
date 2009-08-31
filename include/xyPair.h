#ifndef __VECTOR2D_H
#define __VECTOR2D_H

#include "includes_all.h"

class Vector2D {
    public:
        Vector2D () {};
        Vector2D (u16 X, u16 Y);
        //virtual ~Vector2D();
        Vector2D operator + (Vector2D);
        Vector2D& operator += (Vector2D);

        void clear();

        u16 x;
        u16 y;
    private:
};

#endif
