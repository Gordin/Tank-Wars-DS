#ifndef __XYPAIR_H
#define __XYPAIR_H

#include "includes_all.h"

class xyPair {
    public:
        xyPair () {};
        xyPair (u16 X, u16 Y);
        //virtual ~xyPair();
        xyPair operator + (xyPair);
        xyPair& operator += (xyPair);

        void clear();

        u16 x;
        u16 y;
    private:
};

#endif
