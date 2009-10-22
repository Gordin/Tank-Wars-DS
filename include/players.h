#ifndef __PLAYERS_H
#define __PLAYERS_H

#include "includes_all.h"
#include "gamestates.h"
#include "objects.h"

#define TANK_CENTER_X   5
#define TANK_CENTER_Y   5
#define TANK_HEIGHT     5
#define TANK_WIDTH      9
#define TANK_RADIUS_X   4
#define TANK_RADIUS_Y   4

class player: public object {
    public:
        player ();
        player (u8 pid);
        virtual ~player();

        void shoot();
        void checkSides();
        void checkGround();
        void initialFall();

        static u16 sprite[64];
        static u8 count;
        static u8 hasTurn;

        u8 pid;
        u16 angle;
        u16 power;
        u16 men;
    private:
        void setSprite();
};

#endif
