#include "include/Game/Components/Inventory.h"

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
