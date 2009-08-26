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
        u16 angele;
        u16 power;
        u16 men;
    private:
};

class playerset {
    public:
        playerset (u8 playercount);
        virtual ~playerset();

        void updateOAM();

        u8 playercount;
        player * all;
    private:
};

