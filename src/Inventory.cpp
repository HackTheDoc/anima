#include "include/Game/Components/Inventory.h"

#include "include/struct.h"

Inventory::Inventory() {
    capacity = 0;
    item = {};
}

Inventory::Inventory(const Struct::Inventory& inv) {
    capacity = inv.capacity;

    for (const auto& id : inv.items) {
        Item* i = Item::Create(id.id);
        i->collider->place(id.pos);
        item.push_back(i);
    }
}

Struct::Inventory Inventory::getStructure() {
    Struct::Inventory inv;
    inv.capacity = capacity;

    for (const auto& i : item) 
        inv.items.push_back(i->getStructure());
    
    return inv;
}

bool Inventory::is_full() {
    return item.size() == capacity;
}

bool Inventory::is_empty() {
    return item.size() == 0;
}

bool Inventory::try_consume(const Item::ID id) {
    bool found = false;

    auto it = item.cbegin();
    while (it != item.cend() && !found) {
        Item* i = *it;
        if (i->id == id) {
            item.erase(it);
            found = true;
        }
        it++;
    }

    return found;
}

Item* Inventory::extract_random_item() {
    int it = rand() % item.size();
    Item* i = item[it];
    item.erase(item.cbegin()+it);
    return i;
}

void Inventory::add_item(Item* i) {
    if (is_full()) return;

    item.push_back(i);
}
