#include "includes_all.h"
#include "videoInit.h"
#include "gamestates.h"

u8 gamestate::state = INIT;

gamestate::gamestate() {

}

gamestate::~gamestate() {

}

void gamestate::videoInit() {
    initVideo();
}
