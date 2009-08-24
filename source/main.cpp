#include "includes_all.h"
#include "includes_debug.h"
#include "includes_main.h"

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
    lnd.Palette[BLACK]  =   BLACK_15BIT;
    lnd.Palette[RED]    =   RED_15BIT;
    lnd.Palette[GREEN]  =   GREEN_15BIT;
    lnd.Palette[BLUE]   =   BLUE_15BIT;
    lnd.Palette[DIRT]   =   DIRT_15BIT;
    lnd.Palette[DARKBG] =   DARKBG_15BIT;
    // Writes Palette to VRAM
    DC_FlushRange(lnd.Palette, BG_PAL_LEN);
    dmaCopy(lnd.Palette, BG_PALETTE, BG_PAL_LEN);
    lnd.fill(BLUE); // makes all pixels of the background blue
    lnd.initCosLandscape(); //Calculates heights for a Landscape
    lnd.fillLandscape(); // Sets the landscape based on heights
}

void updateInput(touchPosition * touch) {
    // Update the key registerts with current values.
    scanKeys();
    // Update the touch scren values.
    touchRead(touch);
}

void spritestuff() {

}

int main() {
    /* Turn on the 2D graphics core. */
    powerOn(POWER_ALL_2D);

    /* Configure the VRAM and background control registers. */
    lcdMainOnBottom(); // Place the main screen on the bottom physical screen
    initVideo(); // Arrange VRAM Banks
    initBackgrounds(); // Configure the background control register

    landscape mountain; // Sets up (empty) landscap-background
    initLandscape(mountain); // Put stuff in the landscape

    // Sets up background preferences and stores background id in bg2
    int bg2 = bgInit(2, BgType_Bmp8, BgSize_B8_256x256, 0,0);

    // *** Spritestuff start ***

    oamInit(&oamMain, SpriteMapping_1D_32, false);


    object tank(0, TANK);

    u8 color = 1;
    // Handmade tanksprite
    // Left part 1. row
    tank.gfx[ 1] =     0 | color    << 8;
    tank.gfx[ 2] = color | color    << 8;
    // Left part 2. row
    tank.gfx[ 4] =     0 | color    << 8;
    tank.gfx[ 5] = color | color    << 8;
    tank.gfx[ 6] = color | color    << 8;
    tank.gfx[ 7] = color | color    << 8;
    // Left part 3. row
    tank.gfx[ 8] =     0 | color    << 8;
    tank.gfx[ 9] = color | color    << 8;
    tank.gfx[10] = color | color    << 8;
    tank.gfx[11] = color | color    << 8;
    // Left part 4. row
    tank.gfx[12] = color | color    << 8;
    tank.gfx[13] = color |     0    << 8;
    tank.gfx[14] = color |     0    << 8;
    tank.gfx[15] = color | color    << 8;
    // Left part 5. row
    tank.gfx[16] = color | color    << 8;
    tank.gfx[17] = color | color    << 8;
    tank.gfx[18] = color | color    << 8;
    tank.gfx[19] = color | color    << 8;
    // Right part 4. row
    tank.gfx[44] = color |     0    << 8;
    // Right part 5. row
    tank.gfx[48] = color |     0    << 8;


    object bomb(1, BOMB);

    // every value has 2! Pixels (1 Pixel -> 8 Bit)
    bomb.gfx[0] = 0 | 1    << 8; // The Bomb
    bomb.gfx[4] = 1 | 1    << 8; // 0 1 0
    bomb.gfx[5] = 1 | 0    << 8; // 1 1 1
    bomb.gfx[8] = 0 | 1    << 8; // 0 1 0

    SPRITE_PALETTE[1] = RGB15(31,31,31);
    
    // *** Spritestuff end   ***
    
    // *** Debug start ***
    iprintf("No Fail!\n");
    // *** Debug end   ***
    
    while(1) { // Main game loop
        mountain.dropLandscape();
        swiWaitForVBlank();
        oamUpdate(&oamMain);
        DC_FlushRange(mountain.Bitmap, BG_BITMAP_LEN);
        dmaCopy(mountain.Bitmap, bgGetGfxPtr(bg2), BG_BITMAP_LEN);
    }
    return 0;
}

