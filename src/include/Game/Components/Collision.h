#pragma once

#include <SDL2/SDL.h>

class Collider;

class Collision {
public:
    static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
    static bool AABB(Collider* colA, Collider* colB);
    static bool WithTile(int x, int y);
};
