#pragma once

#include <vector>

#include "../Items/Items.h"

struct Inventory {
    unsigned int capacity;
    std::vector<Item*> item;
};
