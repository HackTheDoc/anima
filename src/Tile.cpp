#include "include/Game/Map/Tile.h"

#include "include/Game/Game.h"
#include "include/Manager.h"

Tile::Tile(Type t) {
    switch (t) {
    case Tile::Type::GRASS_LEFT:
        srcRect = { 16, 96, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::GRASS_RIGHT:
        srcRect = { 48, 96, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::GRASS_TOP:
        srcRect = { 32, 80, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::GRASS_TOP_LEFT:
        srcRect = { 16, 80, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::GRASS_TOP_RIGHT:
        srcRect = { 48, 80, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::GRASS_BOTTOM:
        srcRect = { 32, 112, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::GRASS_BOTTOM_LEFT:
        srcRect = { 16, 112, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::GRASS_BOTTOM_RIGHT:
        srcRect = { 48, 112, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::WATER:
        srcRect = { 64, 112, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::WATER_TOP_LEFT:
        srcRect = { 64, 80, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::WATER_TOP_RIGHT:
        srcRect = { 80, 80, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::WATER_BOTTOM_LEFT:
        srcRect = { 64, 96, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::WATER_BOTTOM_RIGHT:
        srcRect = { 80, 96, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::MOUNTAIN:
        srcRect = { 32, 48, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::MOUNTAIN_LEFT:
        srcRect = { 16, 48, 16, 16 };
        walkable = true;
        break;
    case Tile::Type::MOUNTAIN_RIGHT:
        srcRect = { 80, 48, 16, 16 };
        walkable = true;
        break;
    case Tile::Type::MOUNTAIN_TOP:
        srcRect = { 32, 16, 16, 16 };
        walkable = true;
        break;
    case Tile::Type::MOUNTAIN_TOP_LEFT:
        srcRect = { 16, 16, 16, 16 };
        walkable = true;
        break;
    case Tile::Type::MOUNTAIN_TOP_RIGHT:
        srcRect = { 80, 16, 16, 16 };
        walkable = true;
        break;
    case Tile::Type::MOUNTAIN_BOTTOM:
        srcRect = { 32, 64, 16, 16 };
        walkable = true;
        break;
    case Tile::Type::MOUNTAIN_BOTTOM_LEFT:
        srcRect = { 16, 64, 16, 16 };
        walkable = true;
        break;
    case Tile::Type::MOUNTAIN_BOTTOM_RIGHT:
        srcRect = { 80, 64, 16, 16 };
        walkable = true;
        break;
    case Tile::Type::MOUNTAIN_TOP_LEFT_INNER:
        srcRect = { 96, 16, 16, 16 };
        walkable = true;
        break;
    case Tile::Type::MOUNTAIN_TOP_RIGHT_INNER:
        srcRect = { 112, 16, 16, 16 };
        walkable = true;
        break;
    case Tile::Type::MOUNTAIN_BOTTOM_LEFT_INNER:
        srcRect = { 96, 32, 16, 16 };
        walkable = true;
        break;
    case Tile::Type::MOUNTAIN_BOTTOM_RIGHT_INNER:
        srcRect = { 112, 32, 16, 16 };
        walkable = true;
        break;
    case Tile::Type::WALL:
        srcRect = { 272, 32, 16, 16 };
        walkable = false;
        break;
    case Tile::Type::GRASS:
    default:
        srcRect = { 32, 96, 16, 16 };
        walkable = true;
        break;
    }
}

Tile::~Tile() {}

void Tile::init(int x, int y) {
    texture = Window::manager->getTexture("ground");;

    place(x, y);

    collider = { 0, 0, Tile::SIZE, Tile::SIZE };
}

void Tile::update() {
    collider.x = position.x - Game::camera.x;
    collider.y = position.y - Game::camera.y;
}

void Tile::draw() {
    Manager::Draw(texture, &srcRect, &collider);

#ifdef DEV_MOD
    if (!walkable)
        Manager::DrawRect(&collider, hue::red);
#endif
}

void Tile::destroy() {
    texture = nullptr;
}

void Tile::place(int x, int y) {
    position.x = x * Tile::SIZE;
    position.y = y * Tile::SIZE;
}
