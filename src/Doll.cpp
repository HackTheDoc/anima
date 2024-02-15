#include "include/Game/Entities/Doll.h"

#include "include/struct.h"

Doll::Doll() {
    type = Type::DOLL;
    inventory.capacity = 1;
}

Doll::Doll(const Inventory& inv) {
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

Struct::Entity Doll::getStructure() {
    const Struct::Doll doll{
        .pos = position,
        .inventory = inventory.getStructure()
    };
    return Struct::Entity{ doll };
}
