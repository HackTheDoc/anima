#include "include/Game/Map/Map.h"

#include "include/Game/Game.h"
#include "include/Game/Components/Collision.h"

Map::Map() {}

Map::~Map() {}

void Map::init(int w, int h) {
    width = w;
    height = h;

    for (int y = 0; y < h; y++) {
        tiles.push_back({});
        for (int x = 0; x < w; x++) {
            tiles[y].push_back(nullptr);
        }
    }
}

void Map::update() {
    for (auto l : tiles) {
        for (auto t : l) {
            t->update();

            if (!t->walkable && Collision::AABB(Game::player->collider->rect, t->collider)) {
                Game::player->reverseMovement();
                Game::player->resetMovement();
            }
        }
    }
}

void Map::render() {
    for (auto l : tiles) {
        for (auto t : l) {
            t->draw();
        }
    }
}

void Map::destroy() {
    for (auto l : tiles) {
        for (auto t : l) {
            t->destroy();
        }
        l.clear();
    }
    tiles.clear();

    width = height = 0;
}

int Map::getHeight() {
    return height;
}

int Map::getWidth() {
    return width;
}

Tile* Map::getTile(int x, int y) {
    return tiles[y][x];
}

void Map::setTile(int x, int y, Tile::Type type) {
    Tile* t = new Tile(type);
    
    t->init(x, y);

    tiles[y][x] = t;
}
