#include "includes_all.h"
#include "gamestates.h"
#include "background.h"
#include "players.h"
#include "bomb.h"

void initBackgrounds() {
    consoleDemoInit(); // Need this for debug-output (iprintf)
}

void initLandscape(landscape &lnd) {
    // Sets up the palette
    lnd.Palette[BLACK]      =   BLACK_15BIT;
    lnd.Palette[RED]        =   RED_15BIT;
    lnd.Palette[GREEN]      =   GREEN_15BIT;
    lnd.Palette[BLUE]       =   BLUE_15BIT;
    lnd.Palette[YELLOW]     =   YELLOW_15BIT;
    lnd.Palette[TURQUIS]    =   TURQUIS_15BIT;
    lnd.Palette[PURPLE]     =   PURPLE_15BIT;
    lnd.Palette[WHITE]      =   WHITE_15BIT;
    lnd.Palette[ORANGE]     =   ORANGE_15BIT;
    lnd.Palette[MAGENTA]    =   MAGENTA_15BIT;
    lnd.Palette[SALMON]     =   SALMON_15BIT;
    lnd.Palette[DIRT]       =   DIRT_15BIT;
    lnd.Palette[DARKBG]     =   DARKBG_15BIT;
    // Gets the DS ready to write to VRAM
    DC_FlushRange(lnd.Palette, BG_PAL_LEN);
    // Writes Palette to VRAM
    dmaCopy(lnd.Palette, BG_PALETTE, BG_PAL_LEN);
    lnd.colorI = DIRT;
    lnd.backgroundColorI = DARKBG;
    lnd.fill(lnd.backgroundColorI); // makes all pixels of the background blue
    lnd.initCosLandscape(); //Calculates heights for a Landscape
    lnd.fillLandscape(); // Sets the landscape based on heights
}

void initObjects(landscape &lnd) {
    /* We just copy over the background palette for sprites, because
     * We don't really need that much different colors...
     */
    for( u16 i = 0; i < BG_PAL_LEN / 2; i++) {
        SPRITE_PALETTE[i] = lnd.Palette[i];
    }
    // This tells the DS how the sprite data is formatted
    oamInit(&oamMain, SpriteMapping_1D_32, false);
}

void updateInput(touchPosition * touch) {
    // Update the key registerts with current values.
    scanKeys();
    // Update the touch scren values.
    touchRead(touch);
}

void updateObjects() {
}

int main() {
    // Initialise gamestate system
    gamestate* game = new gamestate();
    // state is initialised with INIT, just reminding myself...
    game->state = INIT;

    game->videoInit();

    initBackgrounds(); // Configure the background control register

    landscape mountain; // Sets up (empty) landscap-background
    initLandscape(object::land1); // Put stuff in the landscape

    // Sets up background preferences and stores background id in bg2
    int bg2 = bgInit(2, BgType_Bmp8, BgSize_B8_256x256, 0,0);

    initObjects(object::land1); // Sets stuff so objects will work

    // Create 10 players
    u8 players_count = 10;
    player players[players_count];

    // Create 1 bomb
    bomb bombs[1];
    bombs[0].setXY(50, 100);
    bombs[0].acceleration.x = 450;
    bombs[0].acceleration.y = -450;

    // *** Debug start ***
    iprintf("No Fail!\n");
    // *** Debug end   ***

    while(1) { // Main game loop
        // applies Gravity to all objects (moves them)
        for(u8 i = 0; i < players_count; i += 1) {
            players[i].applyGravity();
        }
        bombs[0].applyGravity();
        //mountain.dropLandscape();
        swiWaitForVBlank(); // Wait for a good time to put stuff in OAM
        // Put objects in OAM
        for(u8 i = 0; i < players_count; i += 1) {
            players[i].updateOAM();
        }
        bombs[0].updateOAM();
        oamUpdate(&oamMain);
        // Updates the Landscape and Background
        DC_FlushRange(object::land1.Bitmap, BG_BITMAP_LEN);
        dmaCopy(object::land1.Bitmap, bgGetGfxPtr(bg2), BG_BITMAP_LEN);
    }
    return 0;
}
