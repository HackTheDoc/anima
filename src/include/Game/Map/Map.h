#pragma once

#include <vector>
#include <string>

#include "Tile.h"

namespace Struct {
    struct Map;
};

class Map {
private:
    std::vector<std::vector<Tile*>> tiles;
    int _height, _width;

public:
    Map();
    ~Map();

    void init(const Struct::Map& map);
    void update();
    void render();
    void destroy();
    
    int height();
    int width();

    Tile* getTile(const int x, const int y);
    Tile* getTileAt(const Vector2D& pos);
    void setTile(const int x, const int y, const Tile::Type type);

    Struct::Map getStructure();
};
