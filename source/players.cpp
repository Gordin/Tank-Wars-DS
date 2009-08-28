#include "includes_all.h"
#include "includes_debug.h"
#include "players.h"

u8 player::count = 0;

player::player(): object(count + 1, TANK) {
    count++;
    pid = count;
}

player::player(u8 pid): object(pid, TANK) {
    count++;
    this->pid = pid;
}

player::~player() {
}

playerset::playerset(u8 playercount) {
    // Creates "playercount" players
    this->playercount = playercount;
    all = new player[playercount];
}

void playerset::updateOAM() {
    // Updates OAM for all players
    for( u8 i = 0; i < playercount; i += 1) {
        all[i].updateOAM();
    }
}

playerset::~playerset() {
}
