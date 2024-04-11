#pragma once

#include <SDL2/SDL.h>

#include "Vector2D.h"

class Collider {
public:
    Vector2D position;
    SDL_Rect rect;

    Collider(const int w = 0, const int h = 0);
    ~Collider();

    void update();
    /// TODO: remove collider rendering
    void draw();

    void place(const int x, const int y);
    void place(const Vector2D& pos);
};
