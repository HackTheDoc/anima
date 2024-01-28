#pragma once

#include "Item.h"

class LapisMagicis : public Item {
public:
    LapisMagicis();
    ~LapisMagicis();

    void use() override;
};
