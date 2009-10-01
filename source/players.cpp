#include "includes_all.h"
#include "players.h"

u8 player::count = 0;

// Handmade tanksprite. every value has 2! Pixels (1 Pixel -> 8 Bit)
u16 player::sprite[64] = {
    // Left part of the sprite
                 0,       TSC << 8, TSC | TSC << 8,              0, //  0 -  3
          TSC << 8, TSC | TSC << 8, TSC | TSC << 8, TSC | TSC << 8, //  4 -  7
          TSC << 8, TSC | TSC << 8, TSC | TSC << 8, TSC | TSC << 8, //  8 - 11
    TSC | TSC << 8, TSC           , TSC           , TSC | TSC << 8, // 12 - 15
    TSC | TSC << 8, TSC | TSC << 8, TSC | TSC << 8, TSC | TSC << 8, // 16 - 19
                 0,              0,              0,              0, // 20 - 23
                 0,              0,              0,              0, // 24 - 27
                 0,              0,              0,              0, // 28 - 31
    // Right part of the sprite
                 0,              0,              0,              0, // 32 - 35
                 0,              0,              0,              0, // 36 - 39
                 0,              0,              0,              0, // 40 - 43
    TSC           ,              0,              0,              0, // 44 - 47
    TSC           ,              0,              0,              0, // 48 - 51
                 0,              0,              0,              0, // 52 - 55
                 0,              0,              0,              0, // 56 - 59
                 0,              0,              0,              0  // 60 - 63
};

void player::setSprite() {
    spriteSize = SpriteSize_16x8;
    // oamAllocateGfx allocates memory for the object-sprite
    gfx = oamAllocateGfx(&oamMain, spriteSize, SpriteColorFormat_256Color);
    // This copies the sprite into the object (wrong color)
    memcpy(this->gfx, sprite, sizeof(sprite));
    // This loop replaces the object-color with the player-color
    for(u16 i = 0; i < sizeof(sprite) / 2; i++) {
        if(sprite[i] == TSC) {
            this->gfx[i] = id;
        } else if(sprite[i] == (TSC << 8)) {
            this->gfx[i] = id << 8;
        } else if(sprite[i] == (TSC | TSC << 8)) {
            this->gfx[i] = id | id << 8;
        }
    }
    center.x = 5;
    center.y = 5;
    height = 5;
    radius.x = 4;
    width = 9;
    radius.y = 4;
}

void player::checkSides() {
    s16 Y = getY();
    u8 sheight = SCREEN_HEIGHT - 1;
    // Checks bottom side
    if(Y >= sheight) {
        speed.y = 0;
        setY(sheight);
    }
}

void player::checkGround() {
    s16 X = getX();
    s16 Y = getY();
    initialFall();
    if(object::land1.getPixColorI(X,Y+1) == DIRT) {
        speed.x = 0;
        speed.y = 0;
    }
}

void player::initialFall() {
    /* Removes Landscape under the tank until theres
     * no free space between tank and landscape
     */
    s16 X = getX();
    s16 Y = getY();
    u8 pushDirt = 0;
    for( u8 i = 0; i < 9; i += 1) {
        if(object::land1.getPixColorI((X-4)+i,Y+1) == DIRT) {
            pushDirt++;
        }
    }
    if(pushDirt < 9) {
        for( u8 i = 0; i < 9; i += 1) {
            land1.setPixColorI((X-4)+i, Y+1, object::land1.backgroundColorI);
        }
    }
}

player::player(): object(count + 1, TANK) {
    count++;
    pid = count;
    setSprite();
}

player::player(u8 pid): object(pid, TANK) {
    count++;
    this->pid = pid;
    setSprite();
}

player::~player() {
}

playerset::playerset(u8 playercount) {
    // Creates "playercount" players
    this->playercount = playercount;
    all = new player[playercount];
}

void playerset::updateOAM() {
    // Updates OAM for all players
    for( u8 i = 0; i < playercount; i += 1) {
        all[i].updateOAM();
    }
}

playerset::~playerset() {
}
