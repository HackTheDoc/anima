#pragma once

#include <vector>

#include "../Items/Items.h"

struct Inventory {
    unsigned int capacity{0};
    std::vector<Item*> item{};

    bool is_full();
    bool is_empty();
    bool try_consume(const Item::ID id);

    Item* extract_random_item();
    /// @brief add an item if there is space in the inventory
    void add_item(Item* i);
};
