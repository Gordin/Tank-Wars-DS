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

bomb::bomb(u8 bombtype): object(count++ + count_offset, BOMB) {
    this->bombtype = bombtype;
    setSprite();
}

bomb::bomb(): object(count++ + count_offset, BOMB) {
    this->bombtype = STANDARD_BOMB;
    setSprite();
}

bomb::~bomb() {
}

void bomb::checkSides() {
    s16 X = getX();
    u8 swidth = SCREEN_WIDTH - 1;
    // Checks left and right side
    if((X + radius.x) >= swidth) {
        speed.x = -speed.x;
        setX(swidth - radius.x);
    } else if((X - radius.x) <= 0) {
        speed.x = -speed.x;
        setX(radius.x);
    }
    s16 Y = getY();
    u8 sheight = SCREEN_HEIGHT - 1;
    // Checks bottom side
    if((Y + radius.y) >= sheight) {
        speed.y = -speed.y;
        setY(sheight - radius.y);
    }
}

void bomb::checkGround() {
    s16 X = getX();
    s16 Y = getY();
    // Collision Detection Bomb <-> Landscape
    if(landscape1->getPixColorI(X,Y) == landscape1->colorI) {
        speed.x = -speed.x;
        speed.y = -speed.y;
    }
}

void bomb::setSprite() {
    spriteSize = SpriteSize_8x8;
    // oamAllocateGfx allocates memory for the object-sprite
    gfx = oamAllocateGfx(&oamMain, spriteSize, SpriteColorFormat_256Color);
    // This copies the sprite into the object
    memcpy(this->gfx, sprite, sizeof(sprite));
    center.x = BOMB_CENTER_X;
    center.y = BOMB_CENTER_Y;
    height = BOMB_HEIGHT;
    width = BOMB_WIDTH;
    radius.x = BOMB_RADIUS_X;
    radius.y = BOMB_RADIUS_Y;
    //XXX places the bomb on the screen
    setXY(20 * (id + 1), 15);
}

