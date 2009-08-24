#include "includes_all.h"
#include "includes_debug.h"

#define BOMB    1
#define TANK    2

template <class T>
struct xyPair {
    T x;
    T y;
};

class object {
    public:
        object (u8 object_id, u8 object_type);
        virtual ~object();

        
        u8 id;
        u8 type;
        u8 palette;
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
