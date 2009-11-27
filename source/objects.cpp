#include "includes_all.h"

#include "background.h"
#include "objects.h"

Vector2D object::gravity(0,10);
landscape* object::landscape1;
landscape* object::landscape2;

object::object(u8 id, u8 type) {
    this->type = type;
    this->id = id;
    this->acceleration.x = 0;
    this->acceleration.y = 0;
    this->speed.x = 0;
    this->speed.y = 0;
    this->hide = false;

    updateOAM();
}

object::~object() {

}

void object::applyGravity() {
    speed += acceleration + gravity;
    acceleration.clear();
    for( u8 i = 0; i < (1 << 3); i += 1)
    {
        checkGround();
        checkSides();
        position += (speed / 8);
    }
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

