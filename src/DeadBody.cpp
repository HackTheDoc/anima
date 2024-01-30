#include "include/Game/Entities/DeadBody.h"

DeadBody::DeadBody(Entity::Species species) {
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

EntityStructure DeadBody::getStructure() {
    return {
        .type = type,
        .type2 = ownerType,
        .species = species,
        .name = name,
        .pos = position,
        .npc_hasdialog = ownerHasDialog,
        .behavior = behavior
    };
}
