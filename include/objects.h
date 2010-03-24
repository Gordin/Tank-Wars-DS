#ifndef __OBJECTS_H
#define __OBJECTS_H

#include "includes_all.h"
#include "background.h"

#define BOMB    0
#define TANK    1

class object {
    public:
        object (u8 id, u8 type);
        object ();
        virtual ~object();

        void setX(u16 X);
        void setY(u16 Y);
        u16 getX();
        u16 getY();
        void setXY(u16 X, u16 Y);
        void setHide(bool hide);
        void applyGravity();
        void updateOAM();
        virtual void checkSides() {}
        virtual void checkGround() {}

        //static u8 count;
        static Vector2D gravity;
        static landscape* landscape1;
        static landscape* landscape2;

        u8 id;
        u8 type;
        u8 palette;
        Vector2D center;
        Vector2D position;
        Vector2D speed;
        Vector2D acceleration;
        Vector2D radius;
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
    position.x = ((X - radius.x) << 8); // Shift left to store as fixed point
}

inline void object::setY(u16 Y) {
    position.y = ((Y - radius.y) << 8); // Shift left to store as fixed point
}

inline u16 object::getX() {
    return (position.x >> 8) + radius.x; // Shift right because it's fixed point
}

inline u16 object::getY() {
    return (position.y >> 8) + radius.y; // Shift right because it's fixed point
}

inline void object::setXY(u16 X, u16 Y) {
    setX(X);
    setY(Y);
}

inline void object::setHide(bool hide){
    this->hide = hide;
}

#endif
