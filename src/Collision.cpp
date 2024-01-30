#include "include/Game/Components/Collision.h"

#include "include/Game/Game.h"
#include "include/Game/Components/Collider.h"
#include "include/Game/Map/Tile.h"

namespace Collision {
    bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
        if (
            rectA.x + rectA.w >= rectB.x &&
            rectB.x + rectB.w >= rectA.x &&
            rectA.y + rectA.h >= rectB.y &&
            rectB.y + rectB.h >= rectA.y
        ) {
            return true;
        }
        return false;
    }

    bool AABB(const Collider* colA, const Collider* colB) {
        if (colA == nullptr || colB == nullptr) return false;
        return AABB(colA->rect, colB->rect);
    }

    bool AABB(const Collider* col, const Tile* t) {
        if (col == nullptr || t == nullptr) return false;
        return AABB(col->rect, t->collider);
    }
}