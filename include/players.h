#ifndef __PLAYERS_H
#define __PLAYERS_H

#include "includes_all.h"
#include "includes_debug.h"
#include "objects.h"

class player: public object {
    public:
        player ();
        player (u8 pid);
        virtual ~player();

        static u8 count;
        static u8 hasTurn;

        u8 pid;
        u16 angle;
        u16 power;
        u16 men;
    private:
};

// Class to put all players in one place
class playerset {
    public:
        playerset (u8 playercount);
        virtual ~playerset();

        void updateOAM();

        u8 playercount;
        player * all;
    private:
};

#endif
