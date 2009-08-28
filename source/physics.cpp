#include "includes_all.h"
#include "includes_debug.h"
#include "physics.h"

physicsEngine::physicsEngine(xyPair gravity) {
    this->gravity = gravity;
}

void physicsEngine::applyGravity(object &pl) {
    pl.speed += pl.acceleration + gravity;
    pl.position += pl.speed;
}

physicsEngine::~physicsEngine() {

}
