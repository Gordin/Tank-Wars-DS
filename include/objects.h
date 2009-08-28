#ifndef __OBJECTS_H
#define __OBJECTS_H

#include "includes_all.h"
#include "includes_debug.h"

#define BOMB    0
#define TANK    1

class xyPair {
    public:
        xyPair () {};
        //virtual ~xyPair();
        xyPair operator + (xyPair);
        xyPair& operator += (xyPair);

        u16 x;
        u16 y;
    private:
};

class object {
    public:
        object (u8 id, u8 type);
        virtual ~object();

        void setX(u16 X);
        void setY(u16 Y);
        void setXY(u16 X, u16 Y);
        void setHide(bool hide);

        void updateOAM();

        static u8 count;
        static u16 tanksprite[64];
        static u16 bombsprite[32];

        u8 id;
        u8 type;
        u8 palette;
        bool hide;
        xyPair center;
        xyPair position;
        xyPair speed;
        xyPair acceleration;
        u8 height;
        u8 width;
        u8 height_sprite;
        u8 width_sprite;
        u16 * gfx;
        SpriteSize spriteSize;
    private:
};

inline void object::setX(u16 X) {
    position.x = (X << 8);
}

inline void object::setY(u16 Y) {
    position.y = (Y << 8);
}

inline void object::setXY(u16 X, u16 Y) {
    setX(X);
    setY(Y);
}

inline void object::setHide(bool hide){
    this->hide = hide;
}

#endif
