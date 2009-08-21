#include <nds.h>

#include <stdio.h>
#include <assert.h>

#include "background.h"

void initVideo() {
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
                 DISPLAY_BG2_ACTIVE);
                 //DISPLAY_BG3_ACTIVE | // Enable BG3 for display
                 //DISPLAY_SPR_ACTIVE | // Enable sprites for display
                 //DISPLAY_SPR_1D );    // Enable 1D tiled sprites

    /* Set the video mode on the sub screen. */
    videoSetModeSub(MODE_5_2D | // Set the graphics mode to Mode 5
                    DISPLAY_BG3_ACTIVE); // Enable BG3 for display
}

void initBackgrounds() {

}

void updateInput(touchPosition * touch) {
    // Update the key registerts with current values.
    scanKeys();
    // Update the touch scren values.
    touchRead(touch);
}


int main() {
    /* Turn on the 2D graphics core. */
    powerOn(POWER_ALL_2D);

    /* Configure the VRAM and background control registers. */
    lcdMainOnBottom(); // Place the main screen on the bottom physical screen
    initVideo(); // Arrange VRAM Banks
    initBackgrounds(); // Configure the background control register

    landscape mountain(256);
    mountain.Palette[BLACK]     =   RGB15(0,0,0);
    mountain.Palette[RED]       =   RGB15(31,0,0);
    mountain.Palette[GREEN]     =   RGB15(0,31,0);
    mountain.Palette[BLUE]      =   RGB15(0,0,31);
    mountain.fill(GREEN);
    for( u16 i = 0; i < 256; i += 1)
    {
        mountain.setPixelPaletteIndex(i,0,RED);
        mountain.setPixelPaletteIndex(i,191,RED);
        mountain.setPixelPaletteIndex(0,i,RED);
        mountain.setPixelPaletteIndex(255,i,RED);
    }
    
	int bg2 = bgInit(2, BgType_Bmp8, BgSize_B8_256x256, 0,0);

	dmaCopy(mountain.Bitmap, bgGetGfxPtr(bg2), 256*192);
	dmaCopy(mountain.Palette, BG_PALETTE, 256*2);

    consoleDemoInit();
    iprintf("%i\n", mountain.readPixelPaletteIndex(100,100));
    iprintf("No Fail!");
    while(1)swiWaitForVBlank();
	return 0;
}
