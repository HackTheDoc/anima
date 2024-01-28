#pragma once

#include "Collider.h"

class Tile;

class TileCollider : public Collider {
public:
    TileCollider(Tile* o = nullptr);
    ~TileCollider();

    void setOwner(Tile* o);
    void setSize(int w, int h);

protected:
    Tile* owner;
};
