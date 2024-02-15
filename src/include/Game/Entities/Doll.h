#pragma once

#include "Entity.h"

class Doll : public Entity  {
public:
    Doll();
    Doll(const Inventory& inv);
    ~Doll();

    void init() override;

    Struct::Entity getStructure();
};
