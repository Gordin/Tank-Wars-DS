#include "background.h"

drawBackground::drawBackground(u16 x, u8 y) {
    width = x;
    height = y;
    Bitmap = new u8[BG_BITMAP_LEN];
    Palette = new u16[BG_PAL_LEN];
}

drawBackground::drawBackground() {
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
    height = new u8[width];
}

landscape::~landscape() {
    delete height;
}
