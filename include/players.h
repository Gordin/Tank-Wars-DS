#ifndef __PLAYERS_H
#define __PLAYERS_H

#include "includes_all.h"
#include "objects.h"

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
