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
            // Only Left pixel
            this->gfx[i] = (id + 1);
        } else if(sprite[i] == (TSC << 8)) {
            // Only right pixel
            this->gfx[i] = (id + 1) << 8;
        } else if(sprite[i] == (TSC | TSC << 8)) {
            // Both pixels
            this->gfx[i] = (id + 1) | (id + 1) << 8;
        }
    }
    center.x = TANK_CENTER_X;
    center.y = TANK_CENTER_Y;
    height = TANK_HEIGHT;
    width = TANK_WIDTH;
    radius.x = TANK_RADIUS_X;
    radius.y = TANK_RADIUS_Y;
    //XXX places the tank on the screen
    setXY(20 * (id + 1), 15);
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
    // Collision Detection Player <-> Landscape
    if(object::land1.getPixColorI(X,Y+1) == land1.colorI) {
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
    // Checks if tank is standing on the landscape
    for(u8 i = 0; i < width; i += 1) {
        if(object::land1.getPixColorI((X-radius.x)+i,Y+1) == land1.colorI) {
            pushDirt++;
        }
    }
    /* If the tank is not standing completely on the landscape, remove dirt
     * inside the tank
     */
    if(pushDirt < width) {
        for(u8 i = 0; i < width; i += 1) {
            land1.setPixColorI((X-radius.x)+i, Y+1, object::land1.backgroundColorI);
        }
    }
}

player::player(): object(count++, TANK) {
    pid = count;
    setSprite();
}

player::player(u8 pid): object(count++, TANK) {
    this->pid = pid;
    setSprite();
}

player::~player() {
}
