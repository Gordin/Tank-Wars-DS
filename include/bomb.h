#ifndef __BOMB_H
#define __BOMB_H

#include "includes_all.h"
#include "objects.h"

#define STANDARD_BOMB   0
#define BOMB_CENTER_X   1
#define BOMB_CENTER_Y   1
#define BOMB_HEIGHT     3
#define BOMB_WIDTH      3
#define BOMB_RADIUS_X   1
#define BOMB_RADIUS_Y   1

class bomb: public object {
    public:
        bomb ();
        bomb (u8 bombtype);
        virtual ~bomb();

        void checkSides();
        void checkGround();

        static u16 sprite[32];
        static u8 count;
        static u8 count_offset;

        u8 power;
        u8 bombtype;
    private:
        void setSprite();
};

#endif
