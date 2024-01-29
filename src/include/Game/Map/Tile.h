#pragma once

#include <SDL2/SDL.h>

#include "../../Window.h"

#include "../Components/Vector2D.h"

class Tile {
public:
    static constexpr int SIZE = 128;

    enum Type {
        // Grass Tiles
        GRASS,
        GRASS_LEFT,
        GRASS_RIGHT,
        GRASS_TOP,
        GRASS_TOP_LEFT,
        GRASS_TOP_RIGHT,
        GRASS_BOTTOM,
        GRASS_BOTTOM_LEFT,
        GRASS_BOTTOM_RIGHT,

        // Water Tiles
        WATER,
        WATER_TOP_LEFT,
        WATER_TOP_RIGHT,
        WATER_BOTTOM_LEFT,
        WATER_BOTTOM_RIGHT,

        // Mountain Tiles
        MOUNTAIN,
        MOUNTAIN_LEFT,
        MOUNTAIN_RIGHT,
        MOUNTAIN_TOP,
        MOUNTAIN_TOP_LEFT,
        MOUNTAIN_TOP_RIGHT,
        MOUNTAIN_BOTTOM,
        MOUNTAIN_BOTTOM_LEFT,
        MOUNTAIN_BOTTOM_RIGHT,
        MOUNTAIN_TOP_LEFT_INNER,
        MOUNTAIN_TOP_RIGHT_INNER,
        MOUNTAIN_BOTTOM_LEFT_INNER,
        MOUNTAIN_BOTTOM_RIGHT_INNER
    };

    Vector2D position;
    SDL_Rect collider;
    bool walkable;

    Tile(Type t = Type::GRASS);
    ~Tile();

    virtual void init(int x = 0, int y = 0);
    void update();
    void draw();
    void destroy();

    void place(int x, int y);

protected:
    SDL_Texture* texture;
    SDL_Rect srcRect;
};
