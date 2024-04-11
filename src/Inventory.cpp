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

bool Inventory::isFull() {
    return item.size() == capacity;
}

bool Inventory::isEmpty() {
    return item.size() == 0;
}

bool Inventory::tryConsume(const Item::ID id) {
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

Item* Inventory::extractRandomItem() {
    int it = rand() % item.size();
    Item* i = item[it];
    item.erase(item.cbegin() + it);
    return i;
}

void Inventory::addItem(Item* i) {
    if (isFull()) return;

    item.push_back(i);
}
