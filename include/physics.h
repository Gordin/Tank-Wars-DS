#ifndef __PHYSICS_H
#define __PHYSICS_H

#include "includes_all.h"
#include "includes_debug.h"
#include "players.h"

class physicsEngine
{
    public:
        physicsEngine (xyPair gravity);
        virtual ~physicsEngine();

        void applyGravity(player &pl);

        xyPair gravity;

    private:
};

#endif
