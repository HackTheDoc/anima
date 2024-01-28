#include "include/Game/Components/TileCollider.h"

#include "include/Game/Map/Tiles.h"

TileCollider::TileCollider(Tile* o) {
    rect = {0,0,0,0};
    setOwner(o);
}

TileCollider::~TileCollider() {}

void TileCollider::setOwner(Tile* o) {
    owner = o;
    setSize(Tile::SIZE, Tile::SIZE);
}

void TileCollider::setSize(int w, int h) {
    rect.w = w;
    rect.h = h;
}
