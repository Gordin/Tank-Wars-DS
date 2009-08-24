#include "includes_all.h"
#include "includes_debug.h"
#include "objects.h"

object::object(u8 object_id, u8 object_type) {
    type = object_type;
    if(type == TANK) {
        spriteSize = SpriteSize_16x8;
    } else {
        spriteSize = SpriteSize_8x8;
    }
    id = object_id;

    gfx = oamAllocateGfx(&oamMain, spriteSize,
                              SpriteColorFormat_256Color);
    
    oamSet(&oamMain,        //main graphics engine context
        id,                  //oam index (0 to 127)
        20 << id, 10,             //x and y pixle location of the sprite
        0,                  //priority, lower renders last (on top)
        0,                  //this is the palette index if multiple palettes
                            //or the alpha value if bmp sprite
        spriteSize,
        SpriteColorFormat_256Color,
        gfx,                //pointer to the loaded graphics
        -1,                 //sprite rotation data
        false,              //double the size when rotating?
        false,              //hide the sprite?
        false, false,       //vflip, hflip
        false               //apply mosaic
        );
}

object::~object() {

}
