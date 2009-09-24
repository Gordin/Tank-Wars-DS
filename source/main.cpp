#include "includes_all.h"
#include "background.h"
#include "players.h"
#include "bomb.h"

void initVideo() {
    // This stuff is copied from pataters tutorial (because it works... 0o)
    /*
     * Map VRAM to display a background on the main and sub screens.
     *
     * The vramSetMainBanks function takes four arguments, one for each of the
     * major VRAM banks. We can use it as shorthand for assigning values to
     * each of the VRAM bank's control registers.
     *
     * We map  banks A and B to main screen background memory. This gives us
     * 256KB, which is a healty amount for 16-bit graphics.
     *
     * We map bank C to sub screen background memory.
     *
     * We map bank D to LCD. This setting is generally used for when we aren't
     * using a particular bank.
     *
     * We map bank E to main screen sprite memory (aka object memory).
     */
    vramSetMainBanks(VRAM_A_MAIN_BG_0x06000000,
                     VRAM_B_MAIN_BG_0x06020000,
                     VRAM_C_SUB_BG_0x06200000,
                     VRAM_D_LCD);

    vramSetBankE(VRAM_E_MAIN_SPRITE);

    /* Set the video mode on the main screen. */
    videoSetMode(MODE_5_2D | // Set the graphics mode to Mode 5
                 DISPLAY_BG2_ACTIVE |
                 DISPLAY_BG3_ACTIVE | // Enable BG3 for display
                 DISPLAY_SPR_ACTIVE | // Enable sprites for display
                 DISPLAY_SPR_1D );    // Enable 1D tiled sprites

    /* Set the video mode on the sub screen. */
    videoSetModeSub(MODE_5_2D | // Set the graphics mode to Mode 5
                    DISPLAY_BG3_ACTIVE); // Enable BG3 for display
}

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
    /* Turn on the 2D graphics core. */
    powerOn(POWER_ALL_2D);

    /* Configure the VRAM and background control registers. */
    lcdMainOnBottom(); // Place the main screen on the bottom physical screen
    initVideo(); // Arrange VRAM Banks
    initBackgrounds(); // Configure the background control register

    landscape mountain; // Sets up (empty) landscap-background
    initLandscape(object::land1); // Put stuff in the landscape

    // Sets up background preferences and stores background id in bg2
    int bg2 = bgInit(2, BgType_Bmp8, BgSize_B8_256x256, 0,0);

    initObjects(object::land1); // Sets stuff so objects will works

    // Create 10 players
    playerset players(10);

    // Create 1 bomb
    bomb bombs[1];
    bombs[0].setXY(50, 100);
    bombs[0].acceleration.x = 450;
    bombs[0].acceleration.y = -450;

    // *** Debug start ***
    iprintf("No Fail!\n");
    // *** Debug end   ***

    //u8 foo = players.all[0].getY();
    //u8 bar = players.all[0].getX();
    while(1) { // Main game loop
        for( u8 i = 0; i < players.playercount; i += 1) {
            players.all[i].applyGravity();
        }
        //printf("%i, %i, %i\n", foo, players.all[0].getY(),
                //object::land1.groundheight[bar]);
        bombs[0].applyGravity();
        //mountain.dropLandscape();
        swiWaitForVBlank();
        players.updateOAM();
        bombs[0].updateOAM();
        oamUpdate(&oamMain);
        //DC_FlushAll();
        DC_FlushRange(object::land1.Bitmap, BG_BITMAP_LEN);
        dmaCopy(object::land1.Bitmap, bgGetGfxPtr(bg2), BG_BITMAP_LEN);
    }
    return 0;
}
