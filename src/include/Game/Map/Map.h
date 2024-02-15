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
    int height, width;

public:
    Map();
    ~Map();

    void init(const Struct::Map& map);
    void update();
    void render();
    void destroy();
    
    int getHeight();
    int getWidth();

    Tile* getTile(int x, int y);
    Tile* getTileAt(Vector2D p);
    void setTile(int x, int y, Tile::Type type);

    Struct::Map getStructure();
};
