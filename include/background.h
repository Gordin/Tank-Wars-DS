#include <nds.h>

#define BG_BITMAP_LEN 49152
#define BG_PAL_LEN 256

#define BLACK   0
#define RED     1
#define GREEN   2
#define BLUE    3

class drawBackground {
    public:
        drawBackground(u16 x, u8 y); 
        drawBackground(); 
        virtual ~drawBackground();

        u16 readPixelColor(u8 x, u8 y);
        u8 readPixelPaletteIndex(u8 x, u8 y);
        void setPixelPaletteIndex(u8 x, u8 y, u8 colorIndex);
        void fill(u8 color);

        u8 *Bitmap;
        u16 *Palette;
    private:
        u16 width;
        u8 height;
    
        u16 getArrayPosition(u8 x, u8 y);
};

class landscape: public drawBackground {
    public:
        landscape(u16 width);
        virtual ~landscape();

        u8 * height;
    private:
        
};

