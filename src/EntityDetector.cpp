#include "include/Game/Components/EntityDetector.h"

#include "include/Game/Game.h"
#include "include/Game/Entities/Entity.h"

#include "include/Manager.h"

EntityDetector::EntityDetector(Entity* o) {
    rect = {0,0,0,0};
    setOwner(o);
    rect.w = owner->width;
    rect.h = owner->height;
}

EntityDetector::~EntityDetector() {}

void EntityDetector::update() {
    position.x = owner->position.x - 3 * rect.w / 8;
    position.y = owner->position.y - rect.h / 4;

    Collider::update();
}

void EntityDetector::draw() {
    Manager::DrawRect(&rect, hue::green);
}

void EntityDetector::setOwner(Entity* o) {
    owner = o;
}
