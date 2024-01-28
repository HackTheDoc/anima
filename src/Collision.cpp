#include "include/Game/Components/Collision.h"

#include "include/Game/Game.h"
#include "include/Game/Components/Collider.h"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
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

bool Collision::AABB(Collider* colA, Collider* colB) {
    if (colA == nullptr || colB == nullptr) return false;
    return AABB(colA->rect, colB->rect);
}

bool Collision::WithTile(int x, int y) {
    if (x <= 0 || x >= Game::island->map->getWidth() ||
        y <= 0 || y >= Game::island->map->getHeight()
    ) {
        return true;
    }
    if (Game::island->map->getTile(x, y)->collider) {
        return Collision::AABB(Game::island->map->getTile(x,y)->collider, Game::player->collider);
    }
    return false;
}
