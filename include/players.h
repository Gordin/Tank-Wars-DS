#include "includes_all.h"
#include "includes_debug.h"
#include "objects.h"

class player: public object {
    public:
        player (u8 pid);
        virtual ~player();

        static u8 hasTurn;

        u8 pid;
        u16 angele;
        u16 power;
        u16 men;
    private:
};

