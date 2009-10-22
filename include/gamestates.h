#ifndef __GAMESTATES_H
#define __GAMESTATES_H

#include "background.h"

#define INIT            0
#define MENU            1
#define BATTLE_INIT     2
#define BATTLE_START    3
#define BATTLE_AIM      4
#define BATTLE_SHOOT    5

class gamestate {
    public:
        gamestate ();
        virtual ~gamestate();

        void loop();
        void videoInit();
        void initLandscape();
        void initObjects();

        static u8 state;

        landscape landscape1;
        landscape landscape2;

        u8 id;
    private:
};

#endif
