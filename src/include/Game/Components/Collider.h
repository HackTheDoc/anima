#pragma once

#include <SDL2/SDL.h>

#include "Vector2D.h"

class Collider {
public:
    Vector2D position;
    SDL_Rect rect;

    Collider();
    Collider(int w, int h);
    ~Collider();

    void update();
    void draw(); // TODO remove collider rendering

    void place(int x, int y);
    void place(Vector2D pos);
};
