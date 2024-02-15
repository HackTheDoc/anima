#pragma once

#include "Entity.h"

class DeadBody : public Entity {
public:
    Entity::Type ownerType;
    bool ownerHasDialog;

    DeadBody(const Entity::Species species);
    ~DeadBody();

    void init() override;

    Struct::Entity getStructure();
};
