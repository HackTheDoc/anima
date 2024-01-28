#pragma once

#include <SDL2/SDL.h>

#include "../../Window.h"

#include "../Components/Vector2D.h"
#include "../Components/TileCollider.h"

class Tile
{
public:
    static constexpr int SIZE = 128;

    enum Type
    {
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
    TileCollider *collider;

    Tile();
    ~Tile();

    virtual void init(int x = 0, int y = 0);
    void update();
    void draw();
    void destroy();

    void place(int x, int y);

protected:
    SDL_Texture *texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
};

#pragma region GRASS TILES

class GrassTile : public Tile
{
public:
    void init(int x = 0, int y = 0) override
    {
        Tile::init(x, y);

        texture = Window::manager->getTexture("ground");

        srcRect = {32, 96, 16, 16};
    }
};

class GrassLeftBorderTile : public GrassTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        GrassTile::init(x, y);

        srcRect = {16, 96, 16, 16};

        collider = new TileCollider(this);
        collider->place(position);
    }
};

class GrassRightBorderTile : public GrassTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        GrassTile::init(x, y);

        srcRect = {48, 96, 16, 16};

        collider = new TileCollider(this);
        collider->place(position);
    }
};

class GrassTopBorderTile : public GrassTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        GrassTile::init(x, y);

        srcRect = {32, 80, 16, 16};

        collider = new TileCollider(this);
        collider->place(position);
    }
};

class GrassTopLeftBorderTile : public GrassTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        GrassTile::init(x, y);

        srcRect = {16, 80, 16, 16};

        collider = new TileCollider(this);
        collider->place(position);
    }
};

class GrassTopRightBorderTile : public GrassTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        GrassTile::init(x, y);

        srcRect = {48, 80, 16, 16};

        collider = new TileCollider(this);
        collider->place(position);
    }
};

class GrassBottomBorderTile : public GrassTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        GrassTile::init(x, y);

        srcRect = {32, 112, 16, 16};

        collider = new TileCollider(this);
        collider->place(position);
    }
};

class GrassBottomLeftBorderTile : public GrassTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        GrassTile::init(x, y);

        srcRect = {16, 112, 16, 16};

        collider = new TileCollider(this);
        collider->place(position);
    }
};

class GrassBottomRightBorderTile : public GrassTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        GrassTile::init(x, y);

        srcRect = {48, 112, 16, 16};

        collider = new TileCollider(this);
        collider->place(position);
    }
};

#pragma endregion

#pragma region WATER TILES

class WaterTile : public Tile
{
public:
    void init(int x = 0, int y = 0) override
    {
        Tile::init(x, y);
        texture = Window::manager->getTexture("ground");

        srcRect = {64, 112, 16, 16};

        collider = new TileCollider(this);
        collider->place(position);
    }
};

class WaterTopLeftTile : public WaterTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        WaterTile::init(x, y);

        srcRect = {64, 80, 16, 16};
    }
};

class WaterTopRightTile : public WaterTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        WaterTile::init(x, y);

        srcRect = {80, 80, 16, 16};
    }
};

class WaterBottomLeftTile : public WaterTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        WaterTile::init(x, y);

        srcRect = {64, 96, 16, 16};
    }
};

class WaterBottomRightTile : public WaterTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        WaterTile::init(x, y);

        srcRect = {80, 96, 16, 16};
    }
};

#pragma endregion

#pragma region MOUNTAIN TILES

class MountainTile : public Tile
{
public:
    void init(int x = 0, int y = 0) override
    {
        Tile::init(x, y);
        texture = Window::manager->getTexture("ground");

        srcRect = {32, 48, 16, 16};

        collider = new TileCollider(this);
        collider->place(position);
    }
};

class MountainLeftBorderTile : public MountainTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        MountainTile::init(x, y);

        srcRect = {16, 48, 16, 16};
    }
};

class MountainRightBorderTile : public MountainTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        MountainTile::init(x, y);

        srcRect = {80, 48, 16, 16};
    }
};

class MountainTopBorderTile : public MountainTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        MountainTile::init(x, y);

        srcRect = {32, 16, 16, 16};
    }
};

class MountainTopLeftBorderTile : public MountainTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        MountainTile::init(x, y);

        srcRect = {16, 16, 16, 16};
    }
};

class MountainTopRightBorderTile : public MountainTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        MountainTile::init(x, y);

        srcRect = {80, 16, 16, 16};
    }
};

class MountainBottomBorderTile : public MountainTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        MountainTile::init(x, y);

        srcRect = {32, 64, 16, 16};
    }
};

class MountainBottomLeftBorderTile : public MountainTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        MountainTile::init(x, y);

        srcRect = {16, 64, 16, 16};
    }
};

class MountainBottomRightBorderTile : public MountainTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        MountainTile::init(x, y);

        srcRect = {80, 64, 16, 16};
    }
};

class MountainTopLeftInnerBorderTile : public MountainTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        MountainTile::init(x, y);

        srcRect = {96, 16, 16, 16};
    }
};

class MountainTopRightInnerBorderTile : public MountainTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        MountainTile::init(x, y);

        srcRect = {112, 16, 16, 16};
    }
};

class MountainBottomLeftInnerBorderTile : public MountainTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        MountainTile::init(x, y);

        srcRect = {96, 32, 16, 16};
    }
};

class MountainBottomRightInnerBorderTile : public MountainTile
{
public:
    void init(int x = 0, int y = 0) override
    {
        MountainTile::init(x, y);

        srcRect = {112, 32, 16, 16};
    }
};

#pragma endregion
