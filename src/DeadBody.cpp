#include "include/Game/Entities/DeadBody.h"

#include "include/struct.h"

DeadBody::DeadBody(const Entity::Species species) {
    type = Entity::Type::DEAD_BODY;
    ownerType = Type::UNKNOWN;
    this->species = species;
    ownerHasDialog = false;
};

DeadBody::~DeadBody() {}

void DeadBody::init() {
    Entity::init();

    sprite = new Sprite(this);
    sprite->init(species);
    sprite->useFrame(9, 3);

    detector = new EntityDetector(this);

    walkSpeed = 0;
}

Struct::Entity DeadBody::getStructure() {
    const Struct::DeadBody body{
        .species = species,
        .pos = position,
        .inventory = inventory.getStructure(),
        .o_type = ownerType,
        .o_behavior = behavior,
        .o_name = name,
        .o_hasdialog = ownerHasDialog
    };
    return Struct::Entity{ body };
}
