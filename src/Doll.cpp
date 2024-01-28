#include "include/Game/Entities/Doll.h"

Doll::Doll() {
    type = Type::DOLL;
    inventory.capacity = 1;
}

Doll::Doll(Inventory inv) {
    type = Type::DOLL;
    inventory = inv;
}

Doll::~Doll() {}

void Doll::init() {
    Entity::init();

    sprite = new Sprite(this);
    sprite->init("doll");

    collider = new EntityCollider(this);

    detector = new EntityDetector(this);

    immortal = true;

    walkSpeed = 0;

    /// WARNING: can be modified
    numenLevel = 0;
}

EntityStructure Doll::getStructure() {
    EntityStructure s;
    s.type = Entity::Type::DOLL;
    s.pos = position;
    s.inv = inventory;
    return s;
}
