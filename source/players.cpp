#include "includes_all.h"
#include "includes_debug.h"
#include "players.h"

player::player(u8 pid): object(pid, TANK) {
    this->pid = pid;
}

player::~player() {
}
