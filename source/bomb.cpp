#include "includes_all.h"
#include "bomb.h"

u8 bomb::count = 0;
u8 bomb::count_offset = 10;

bomb::bomb(u8 bombtype): object(count + count_offset + 1, BOMB) {
    count++;
    this->bombtype = bombtype;
}

bomb::bomb(): object(count + count_offset + 1, BOMB) {
    count++;
    this->bombtype = STANDARD_BOMB;
}

bomb::~bomb() {
}
