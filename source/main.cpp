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
    game->bg[2] = bgInit(2, BgType_Bmp8, BgSize_B8_256x256, 0,0);

    game->initSprites(); // Sets stuff so objects will work

    // *** Debug start ***
    iprintf("No Fail!\n");
    // *** Debug end   ***

    while(1) { // Main game loop
        game->battleInit();
    }

    return 0;
}
