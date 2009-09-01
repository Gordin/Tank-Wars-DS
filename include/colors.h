#ifndef __COLORS_H
#define __COLORS_H

// Index of colors in the palette
#define NONE            0
#define RED             1
#define GREEN           2
#define BLUE            3
#define YELLOW          4
#define TURQUIS         5
#define PURPLE          6
#define WHITE           7
#define ORANGE          8
#define MAGENTA         9
#define SALMON          10
#define DIRT            11
#define DARKBG          12
#define BLACK           13

//TankSpriteColor (will be replaced by constructor)
#define TSC 255

// 15 Bit colorvalue for palette-colors
#define RED_15BIT       RGB15(31, 0, 0);
#define GREEN_15BIT     RGB15( 0,31, 0);
#define BLUE_15BIT      RGB15( 0, 0,31);
#define YELLOW_15BIT    RGB15(31,31, 0);
#define TURQUIS_15BIT   RGB15( 0,31,31);
#define PURPLE_15BIT    RGB15(31, 0,31);
#define WHITE_15BIT     RGB15(31,31,31);
#define ORANGE_15BIT    RGB15(31,15, 0);
#define MAGENTA_15BIT   RGB15(31, 0,15);
#define SALMON_15BIT    RGB15(31,15,15);
#define DIRT_15BIT      RGB15( 0,21, 0);
#define DARKBG_15BIT    RGB15( 7, 4, 5);
#define BLACK_15BIT     RGB15( 0, 0, 0);

#endif
