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

void bomb::setsprite() {
    spriteSize = SpriteSize_8x8;
    // oamAllocateGfx allocates memory for the object-sprite
    gfx = oamAllocateGfx(&oamMain, spriteSize, SpriteColorFormat_256Color);
    // This copies the sprite into the object
    memcpy(this->gfx, sprite, sizeof(sprite));
}

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
