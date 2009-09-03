#ifndef __VECTOR2D_H
#define __VECTOR2D_H

#include "includes_all.h"

class Vector2D {
    public:
        Vector2D () {};
        Vector2D (s32 X, s32 Y);
        //virtual ~Vector2D();
        Vector2D operator + (Vector2D);
        Vector2D& operator += (Vector2D);

        void clear();

        s32 x;
        s32 y;
    private:
};

#endif
