#include <nds.h>
#include "background.h"

drawBackground::drawBackground(u16 x, u8 y) {
    width = x;
    height = y;
    Bitmap = new u8[BG_BITMAP_LEN];
    Palette = new u16[BG_PAL_LEN];
}

drawBackground::drawBackground() {
    width = SCREEN_WIDTH;
    height = SCREEN_HEIGHT;
    Bitmap = new u8[BG_BITMAP_LEN];
    Palette = new u16[BG_PAL_LEN];
}

drawBackground::~drawBackground() {
    delete Bitmap;
}

u16 drawBackground::readPixelColor(u8 x, u8 y) {
    return Palette[readPixelPaletteIndex(x,y)];
}

u8 drawBackground::readPixelPaletteIndex(u8 x, u8 y) {
    return Bitmap[getArrayPosition(x,y)];
}

void drawBackground::setPixelPaletteIndex(u8 x, u8 y, u8 colorIndex) {
    Bitmap[getArrayPosition(x,y)] = colorIndex;
}

void drawBackground::fill(u8 color) {
    for(u16 i = 0; i < BG_BITMAP_LEN; i += 1)
    {
        Bitmap[i] = color;
    }
}

u16 drawBackground::getArrayPosition(u8 x, u8 y) {
    return (y << 8) + x;
}

landscape::landscape(u16 width) {
    groundheight = new u8[width];
}

landscape::~landscape() {
    delete groundheight;
}

void landscape::redrawColumn(u8 column) {
    for( u16 i = 0; i < groundheight[column]; i += 1) {
        setPixelPaletteIndex(column, (height-1) - i, DIRT);
    }
}

void landscape::fillLandscape() {
    for( u16 i = 0; i < width; i += 1) {
        redrawColumn(i);
    }
}

void landscape::initLandscape() {
    for( u16 i = 0; i < width; i += 1) {
        groundheight[i] = ((cosLerp(i << 8) + (1 << 12)) >> 7) + 50 ;
        //groundheight[i] = i & 127;
    }
}
