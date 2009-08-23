#include "includes_all.h"
#include "includes_debug.h"
#include "background.h"

drawBackground::drawBackground(u16 x, u16 y) {
    width = x;
    height = y;
    Bitmap = new u8[BG_BITMAP_LEN];
    Palette = new u16[BG_PAL_LEN / 2];
}

drawBackground::drawBackground() {
    width = SCREEN_WIDTH;
    height = SCREEN_HEIGHT;
    Bitmap = new u8[BG_BITMAP_LEN];
    Palette = new u16[BG_PAL_LEN / 2];
}

drawBackground::~drawBackground() {
    delete Bitmap;
}

u16 drawBackground::readPixelColor(u8 x, u8 y) {
    return Palette[getPixColorI(x,y)];
}

u8 drawBackground::getPixColorI(u8 x, u8 y) {
    return Bitmap[getArrayPosition(x,y)];
}

void drawBackground::setPixColorI(u8 x, u8 y, u8 colorIndex) {
    Bitmap[getArrayPosition(x,y)] = colorIndex;
}

void drawBackground::fill(u8 color) {
    for(u16 i = 0; i < BG_BITMAP_LEN; i += 1)
    {
        Bitmap[i] = color;
    }
}

u16 drawBackground::getArrayPosition(u8 x, u8 y) {
    return (y << 8) + x; // Only works if width = 256
    //return (y * width) + x; // Works for all widths
}

landscape::landscape() {
    groundheight = new u8[SCREEN_WIDTH];
    width = SCREEN_WIDTH;
    height = SCREEN_HEIGHT;
}

landscape::landscape(u16 x, u16 y) {
    groundheight = new u8[width];
    width = x;
    height = y;
}

landscape::~landscape() {
    delete groundheight;
}

void landscape::redrawColumn(u16 column) {
    //TODO Change DIRT and BLUE back (test for landscape dropping)
    for(u16 i = 0; i < (height - groundheight[column] + 1); i++) {
        setPixColorI(column, i, DIRT);
    }
    for(u16 i = height - 1; i > (height - groundheight[column]); i--) {
        setPixColorI(column, i, BLUE);
    }
}

void landscape::fillLandscape() {
    for( u16 i = 0; i < width; i += 1) {
        redrawColumn(i);
    }
}

void landscape::initCosLandscape() {
    for( u16 i = 0; i < width; i += 1) {
        // The 8 7 and 50 can be varied
        groundheight[i] = ((cosLerp(i << 8) + (1 << 12)) >> 7) + 50 ;
    }
}

void landscape::dropColumn(u16 column) {
    for(u16 i = (height -1); i > 0; i--)
    {
        if( (getPixColorI(column, i-1) == DIRT) &&
                        (getPixColorI(column, i) == BLUE) ){
            for( u16 k = i; k > 0; k--) {
                setPixColorI(column, k, getPixColorI(column, k-1) );
            }
            setPixColorI(column, 0, BLUE);
            break;
        }
    }
}

void landscape::dropLandscape() {
    for( u16 i = 0; i < width; i++) {
        dropColumn(i);
    }
}

