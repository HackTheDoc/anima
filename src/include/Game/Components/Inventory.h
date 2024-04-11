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

    bool isFull();
    bool isEmpty();
    bool tryConsume(const Item::ID id);

    Item* extractRandomItem();
    /// @brief add an item if there is space in the inventory
    void addItem(Item* i);
};
