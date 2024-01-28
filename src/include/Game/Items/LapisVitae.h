#pragma once

#include "Item.h"

class LapisVitae : public Item {
public:
    LapisVitae();

    ~LapisVitae();

    void use() override;
};
