#include "includes_all.h"
#include "objects.h"
#include "gamestates.h"

u8 gamestate::state = INIT;

gamestate::gamestate() {
}

gamestate::~gamestate() {

}

void gamestate::videoInit() {
    powerOn(POWER_ALL_2D); //Turn on the 2D graphics core.

    lcdMainOnBottom(); // Place the main screen on the bottom physical screen

    /* Configure the VRAM and background control registers. */
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
    // Sets background registers
    consoleDemoInit(); // Need this for debug-output (iprintf)
}

void gamestate::initLandscape() {
    // Sets up the palette
    landscape1.Palette[BLACK]      =   BLACK_15BIT;
    landscape1.Palette[RED]        =   RED_15BIT;
    landscape1.Palette[GREEN]      =   GREEN_15BIT;
    landscape1.Palette[BLUE]       =   BLUE_15BIT;
    landscape1.Palette[YELLOW]     =   YELLOW_15BIT;
    landscape1.Palette[TURQUIS]    =   TURQUIS_15BIT;
    landscape1.Palette[PURPLE]     =   PURPLE_15BIT;
    landscape1.Palette[WHITE]      =   WHITE_15BIT;
    landscape1.Palette[ORANGE]     =   ORANGE_15BIT;
    landscape1.Palette[MAGENTA]    =   MAGENTA_15BIT;
    landscape1.Palette[SALMON]     =   SALMON_15BIT;
    landscape1.Palette[DIRT]       =   DIRT_15BIT;
    landscape1.Palette[DARKBG]     =   DARKBG_15BIT;
    // Gets the DS ready to write to VRAM
    DC_FlushRange(landscape1.Palette, BG_PAL_LEN);
    // Writes Palette to VRAM
    dmaCopy(landscape1.Palette, BG_PALETTE, BG_PAL_LEN);
    landscape1.colorI = DIRT;
    landscape1.backgroundColorI = DARKBG;
    landscape1.fill(landscape1.backgroundColorI); // makes all pixels of the background blue
    landscape1.initCosLandscape(); //Calculates heights for a Landscape
    landscape1.fillLandscape(); // Sets the landscape based on heights

    object::landscape1 = &landscape1;
}

void gamestate::initSprites() {
    /* We just copy over the background palette for sprites, because
     * We don't really need that much different colors...
     */
    for( u16 i = 0; i < BG_PAL_LEN / 2; i++) {
        SPRITE_PALETTE[i] = landscape1.Palette[i];
    }
    // This tells the DS how the sprite data is formatted
    oamInit(&oamMain, SpriteMapping_1D_32, false);
}

void gamestate::battleLoop() {
        oamUpdate(&oamMain);
        // Updates the Landscape and Background
        DC_FlushRange(landscape1.Bitmap, BG_BITMAP_LEN);
        dmaCopy(landscape1.Bitmap, bgGetGfxPtr(bg[2]), BG_BITMAP_LEN);
}
