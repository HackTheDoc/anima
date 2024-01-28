#pragma once

#include "Entity.h"

class Doll : public Entity  {
public:
    Doll();
    Doll(Inventory inv);
    ~Doll();

    void init() override;

    EntityStructure getStructure();
};
