#include <nds.h>

#define BG_BITMAP_LEN   49152   // 256 * 192    (All pixels on screen 8Bit)
#define BG_PAL_LEN      512     // 256 * 2      (256 colors 16Bit)

// Index of colors in the palette
#define BLACK           0
#define RED             1
#define GREEN           2
#define BLUE            3
#define DIRT            4
#define DARKBG          5
// 15 Bit colorvalue for palette-colors
#define BLACK_15BIT     RGB15( 0, 0, 0);
#define RED_15BIT       RGB15(31, 0, 0);
#define GREEN_15BIT     RGB15( 0,31, 0);
#define BLUE_15BIT      RGB15( 0, 0,31);
#define DIRT_15BIT      RGB15( 0,21, 0);
#define DARKBG_15BIT    RGB15( 7, 4, 5);

class drawBackground {
    public:
        drawBackground(u16 x, u16 y);
        drawBackground();
        virtual ~drawBackground();

        u16 readPixelColor(u8 x, u8 y);
        // inline because those will be called all the time 0o
        inline u8 getPixColorI(u8 x, u8 y);
        inline void setPixColorI(u8 x, u8 y, u8 colorIndex);
        void fill(u8 color);

        u8 *Bitmap;
        u16 *Palette;
        u16 width;
        u16 height;
    private:
        inline u16 getArrayPosition(u8 x, u8 y);
};

class landscape: public drawBackground {
    public:
        landscape();
        landscape(u16 width, u16 height);
        virtual ~landscape();

        void redrawColumn(u16 column);
        void fillLandscape();
        void initCosLandscape();
        void dropColumn(u16 column);
        void dropLandscape();

        u8 * groundheight;
    private:
};

