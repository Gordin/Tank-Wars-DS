#ifndef __GAMESTATES_H
#define __GAMESTATES_H

#include "background.h"
#include "objects.h"
#include "bomb.h"
#include "players.h"

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
        void initSprites();
        void battleInit();
        void battlePlayerControl();
        void battleAction();
        void battleLoop();

        static u8 state;
        u8 players_count;

        // Max values (Maybe change Bomb value?)
        bomb bombs[10];
        player players[10];

        // 4 different backgrounds possible
        u8 bg[4];

        landscape landscape1;
        landscape landscape2;

        u8 id;
    private:
};

#endif
