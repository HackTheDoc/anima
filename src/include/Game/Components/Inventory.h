#pragma once

#include <vector>

#include "../Items/Items.h"

struct Inventory {
    unsigned int capacity{0};
    std::vector<Item*> item{};
};
