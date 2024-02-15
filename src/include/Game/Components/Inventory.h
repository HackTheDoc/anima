#pragma once

#include <vector>

#include "../Items/Items.h"

namespace Struct {
    struct Inventory;
};

struct Inventory {
    unsigned int capacity;
    std::vector<Item*> item;

    Inventory();
    Inventory(const Struct::Inventory& inv);
    Struct::Inventory getStructure();

    bool is_full();
    bool is_empty();
    bool try_consume(const Item::ID id);

    Item* extract_random_item();
    /// @brief add an item if there is space in the inventory
    void add_item(Item* i);
};
