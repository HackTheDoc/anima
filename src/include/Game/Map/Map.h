#pragma once

#include <vector>
#include <string>

#include "Tiles.h"

class Map {
private:
    std::vector<std::vector<Tile*>> tiles;
    int height, width;

public:
    Map();
    ~Map();

    void init(int w, int h);
    void update();
    void render();
    void destroy();
    
    int getHeight();
    int getWidth();

    Tile* getTile(int x, int y);
    void setTile(int x, int y, Tile::Type type);
};
