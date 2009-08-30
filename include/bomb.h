#ifndef __BOMB_H
#define __BOMB_H

#include "includes_all.h"
#include "objects.h"

#define STANDARD_BOMB 0

class bomb: public object {
    public:
        bomb ();
        bomb (u8 bombtype);
        virtual ~bomb();

        static u8 count;
        static u8 count_offset;

        u8 power;
        u8 bombtype;
    private:
};

#endif