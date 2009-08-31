#ifndef __OBJECTS_H
#define __OBJECTS_H

#include "includes_all.h"

#define BOMB    0
#define TANK    1

class object {
    public:
        object (u8 id, u8 type);
        virtual ~object();

        void setX(u16 X);
        void setY(u16 Y);
        void setXY(u16 X, u16 Y);
        void setHide(bool hide);
        void applyGravity();
        void updateOAM();

        static u8 count;
        static u16 tanksprite[64];
        static u16 bombsprite[32];
        static Vector2D gravity;

        u8 id;
        u8 type;
        u8 palette;
        Vector2D center;
        Vector2D position;
        Vector2D speed;
        Vector2D acceleration;
        u8 height;
        u8 width;
        u8 height_sprite;
        u8 width_sprite;
        u16 * gfx;
        SpriteSize spriteSize;
    private:
        bool hide;
};

inline void object::setX(u16 X) {
    position.x = (X << 8); // Shift right to store as fixed point
}

inline void object::setY(u16 Y) {
    position.y = (Y << 8); // Shift right to store as fixed point
}

inline void object::setXY(u16 X, u16 Y) {
    setX(X);
    setY(Y);
}

inline void object::setHide(bool hide){
    this->hide = hide;
}

#endif
