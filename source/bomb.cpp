#include "includes_all.h"
#include "bomb.h"

u8 bomb::count = 0;
u8 bomb::count_offset = 10;

// Handmade bombsprite. every value has 2! Pixels (1 Pixel -> 8 Bit)
u16 bomb::sprite[32] = {
    // Rows:      0 1    2 3   4 5  6 7
            WHITE << 8,     0,  0,   0,
    WHITE | WHITE << 8, WHITE,  0,   0,
            WHITE << 8
};

bomb::bomb(u8 bombtype): object(count + count_offset + 1, BOMB) {
    count++;
    this->bombtype = bombtype;
    setsprite();
}

bomb::bomb(): object(count + count_offset + 1, BOMB) {
    count++;
    this->bombtype = STANDARD_BOMB;
    setsprite();
}

bomb::~bomb() {
}

void bomb::checkSides() {
    s16 X = getX();
    u8 swidth = SCREEN_WIDTH - 1;
    // Checks left and right side
    if(X >= swidth) {
        speed.x = -speed.x;
        setX(swidth);
    } else if(X <= 0) {
        speed.x = -speed.x;
        setX(0);
    }
    s16 Y = getY();
    u8 sheight = SCREEN_HEIGHT - 1;
    // Checks bottom side
    if(Y >= sheight) {
        speed.y = -speed.y;
        setY(sheight);
    }
}

void bomb::setsprite() {
    spriteSize = SpriteSize_8x8;
    // oamAllocateGfx allocates memory for the object-sprite
    gfx = oamAllocateGfx(&oamMain, spriteSize, SpriteColorFormat_256Color);
    // This copies the sprite into the object
    memcpy(this->gfx, sprite, sizeof(sprite));
    center.x = 1;
    center.y = 1;
    height = 3;
    width = 3;
}

