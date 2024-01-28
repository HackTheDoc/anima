#include "include/Game/Map/Map.h"

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
    Tile* t;
    
    switch (type) {
    case Tile::Type::GRASS:
        t = new GrassTile();
        break;
    case Tile::Type::GRASS_LEFT:
        t = new GrassLeftBorderTile();
        break;
    case Tile::Type::GRASS_RIGHT:
        t = new GrassRightBorderTile();
        break;
    case Tile::Type::GRASS_TOP:
        t = new GrassTopBorderTile();
        break;
    case Tile::Type::GRASS_TOP_LEFT:
        t = new GrassTopLeftBorderTile();
        break;
    case Tile::Type::GRASS_TOP_RIGHT:
        t = new GrassTopRightBorderTile();
        break;
    case Tile::Type::GRASS_BOTTOM:
        t = new GrassBottomBorderTile();
        break;
    case Tile::Type::GRASS_BOTTOM_LEFT:
        t = new GrassBottomLeftBorderTile();
        break;
    case Tile::Type::GRASS_BOTTOM_RIGHT:
        t = new GrassBottomRightBorderTile();
        break;
    case Tile::Type::WATER:
        t = new WaterTile();
        break;
    case Tile::Type::WATER_TOP_LEFT:
        t = new WaterTopLeftTile();
        break;
    case Tile::Type::WATER_TOP_RIGHT:
        t = new WaterTopRightTile();
        break;
    case Tile::Type::WATER_BOTTOM_LEFT:
        t = new WaterBottomLeftTile();
        break;
    case Tile::Type::WATER_BOTTOM_RIGHT:
        t = new WaterBottomRightTile();
        break;
    case Tile::Type::MOUNTAIN:
        t = new MountainTile();
        break;
    case Tile::Type::MOUNTAIN_LEFT:
        t = new MountainLeftBorderTile();
        break;
    case Tile::Type::MOUNTAIN_RIGHT:
        t = new MountainRightBorderTile();
        break;
    case Tile::Type::MOUNTAIN_TOP:
        t = new MountainTopBorderTile();
        break;
    case Tile::Type::MOUNTAIN_TOP_LEFT:
        t = new MountainTopLeftBorderTile();
        break;
    case Tile::Type::MOUNTAIN_TOP_RIGHT:
        t = new MountainTopRightBorderTile();
        break;
    case Tile::Type::MOUNTAIN_BOTTOM:
        t = new MountainBottomBorderTile();
        break;
    case Tile::Type::MOUNTAIN_BOTTOM_LEFT:
        t = new MountainBottomLeftBorderTile();
        break;
    case Tile::Type::MOUNTAIN_BOTTOM_RIGHT:
        t = new MountainBottomRightBorderTile();
        break;
    case Tile::Type::MOUNTAIN_TOP_LEFT_INNER:
        t = new MountainTopLeftInnerBorderTile();
        break;
    case Tile::Type::MOUNTAIN_TOP_RIGHT_INNER:
        t = new MountainTopRightInnerBorderTile();
        break;
    case Tile::Type::MOUNTAIN_BOTTOM_LEFT_INNER:
        t = new MountainBottomLeftInnerBorderTile();
        break;
    case Tile::Type::MOUNTAIN_BOTTOM_RIGHT_INNER:
        t = new MountainBottomRightInnerBorderTile();
        break;
    default:
        t = new Tile();
        break;
    }
    
    t->init(x, y);

    tiles[y][x] = t;
}
