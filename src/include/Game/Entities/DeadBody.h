#pragma once

#include "Entity.h"

class DeadBody : public Entity {
public:
    Type ownerType;
    bool ownerHasDialog;

    DeadBody(const Species species);
    ~DeadBody();

    void init() override;

    Struct::Entity getStructure();
};
