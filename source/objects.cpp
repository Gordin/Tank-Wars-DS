#include "includes_all.h"

#include "background.h"
#include "objects.h"

//TankSpriteColor (will be replaced by constructor)
#define TSC 255

xyPair object::gravity(0,10);

// Handmade tanksprite. every value has 2! Pixels (1 Pixel -> 8 Bit)
u16 object::tanksprite[64] = {
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

// Handmade bombsprite. every value has 2! Pixels (1 Pixel -> 8 Bit)
u16 object::bombsprite[32] = {
    // Rows:      0 1    2 3   4 5  6 7
            WHITE << 8,     0,  0,   0,
    WHITE | WHITE << 8, WHITE,  0,   0,
            WHITE << 8
};

object::object(u8 id, u8 type) {
    this->type = type;
    if(type == TANK) {
        spriteSize = SpriteSize_16x8;
        // oamAllocateGfx allocates memory for the object-sprite
        gfx = oamAllocateGfx(&oamMain, spriteSize,
                             SpriteColorFormat_256Color);
        // This copies the sprite into the object (wrong
        memcpy(this->gfx, object::tanksprite, sizeof(object::tanksprite));
        // This loop replaces the object-color with the player-color
        for(u16 i = 0; i < sizeof(object::tanksprite) / 2; i++) {
            if(object::tanksprite[i] == TSC) {
                this->gfx[i] = id;
            } else if(object::tanksprite[i] == (TSC << 8)) {
                this->gfx[i] = id << 8;
            } else if(object::tanksprite[i] == (TSC | TSC << 8)) {
                this->gfx[i] = id | id << 8;
            }
        }
    } else  if (type == BOMB) {
        spriteSize = SpriteSize_8x8;
        // oamAllocateGfx allocates memory for the object-sprite
        gfx = oamAllocateGfx(&oamMain, spriteSize,
                             SpriteColorFormat_256Color);
        // This copies the sprite into the object
        memcpy(this->gfx, object::bombsprite, sizeof(object::bombsprite));
    }
    this->id = id;

    setXY(20 * id, 15);
    updateOAM();
}

object::~object() {

}

void object::applyGravity() {
    speed += acceleration + gravity;
    acceleration.clear();
    position += speed;
}

void object::updateOAM() {
    // Writes properties of the object into oam (I guess)
    oamSet(&oamMain,           //main graphics engine context
           id,                 //oam index (0 to 127)
           // positions shifted left to get pixel value from fixed point
           (position.x >> 8),  //x pixel location of the sprite
           (position.y >> 8),  //y pixel location of the sprite
           0,                  //priority, lower renders last (on top)
           0,                  //this is the palette index if multiple palettes
                               //or the alpha value if bmp sprite
           spriteSize,
           SpriteColorFormat_256Color,
           gfx,                //pointer to the loaded graphics
           -1,                 //sprite rotation data
           false,              //double the size when rotating?
           hide,               //hide the sprite?
           false, false,       //vflip, hflip
           false );            //apply mosaic
}

