#pragma once

#include "Item.h"

class Ignotum : public Item {
public:
    Ignotum();
    ~Ignotum();

    void use() override;
};
