#include "includes_all.h"
#include "includes_debug.h"

#define BOMB    0
#define TANK    1

template <class T>
struct xyPair {
    T x;
    T y;
};

class object {
    public:
        object (u8 id, u8 type);
        virtual ~object();

        inline void setX(u16 X) {
            position.x = X;
        }
        inline void setY(u16 Y) {
            position.y = Y;
        }
        inline void setXY(u16 X, u16 Y) {
            position.x = X;
            position.y = Y;
        }
        inline void setHide(bool hide){
            this->hide = hide;
        }
        void updateOAM();

        static u8 count;
        static u16 tanksprite[64];
        static u16 bombsprite[32];

        u8 id;
        u8 type;
        u8 palette;
        bool hide;
        xyPair<u8> center;
        xyPair<u16> position;
        xyPair<u8> speed;
        xyPair<u8> acceleration;
        u8 height;
        u8 width;
        u8 height_sprite;
        u8 width_sprite;
        u16 * gfx;
        SpriteSize spriteSize;
    private:
};

