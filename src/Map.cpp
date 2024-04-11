#include "include/Game/Map/Map.h"

#include "include/Game/Game.h"
#include "include/Game/Components/Collision.h"

#include "include/struct.h"

Map::Map() {}

Map::~Map() {}

void Map::init(const Struct::Map& map) {
    _width = map.width;
    _height = map.height;

    tiles.resize(_height);
    for (int y = 0; y < _height; y++) {
        tiles[y].resize(_width);
        for (int x = 0; x < _width; x++)
            setTile(x, y, map.tiles[y][x]);
    }
}

void Map::update() {
    for (auto l : tiles) {
        for (auto t : l) {
            t->update();

#ifdef DEV_MOD
            if (!Game::player->controlled) continue;
#endif
            if (!t->walkable && Collision::AABB(Game::player->collider->rect, t->collider)) {
                Game::player->reverseMovement();
                Game::player->resetMovement();
            }
        }
    }
}

void Map::render() {
    for (auto l : tiles)
        for (auto t : l)
            t->draw();
}

void Map::destroy() {
    for (auto l : tiles) {
        for (auto t : l)
            t->destroy();
        l.clear();
    }
    tiles.clear();

    _width = _height = 0;
}

int Map::height() {
    return _height;
}

int Map::width() {
    return _width;
}

Tile* Map::getTile(const int x, const int y) {
    return tiles[y][x];
}

Tile* Map::getTileAt(const Vector2D& p) {
    return getTile(round(p.x / Tile::SIZE), round(p.y / Tile::SIZE));
}

void Map::setTile(int x, int y, Tile::Type type) {
    Tile* t = new Tile(type);

    t->init(x, y);

    tiles[y][x] = t;
}

Struct::Map Map::getStructure() {
    Struct::Map map;
    map.width = _width;
    map.height = _height;

    map.tiles.resize(_height);
    for (int y = 0; y < _height; y++) {
        map.tiles[y].resize(_width);
        for (int x = 0; x < _width; x++)
            map.tiles[y][x] = tiles[y][x]->type;
    }

    return map;
}
