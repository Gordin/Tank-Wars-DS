#include "includes_all.h"
#include "gamestates.h"
#include "background.h"
#include "players.h"
#include "bomb.h"

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

    landscape mountain; // Sets up (empty) landscap-background
    game->initLandscape(); // Put stuff in the landscape

    // Sets up background preferences and stores background id in bg2
    int bg2 = bgInit(2, BgType_Bmp8, BgSize_B8_256x256, 0,0);

    game->initSprites(); // Sets stuff so objects will work

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
        DC_FlushRange(LANDSCAPE1.Bitmap, BG_BITMAP_LEN);
        dmaCopy(LANDSCAPE1.Bitmap, bgGetGfxPtr(bg2), BG_BITMAP_LEN);
    }
    return 0;
}
