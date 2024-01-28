#include "include/Game/Map/Tiles.h"

#include "include/Game/Game.h"
#include "include/Manager.h"

Tile::Tile() {}

Tile::~Tile() {}

void Tile::init(int x, int y) {
    texture = nullptr;

    place(x,y);

    srcRect = {0, 0, 16, 16};
    destRect = {0, 0, Tile::SIZE, Tile::SIZE};

    collider = nullptr;
}

void Tile::update() {
    if (collider) collider->update();

    destRect.x = position.x - Game::camera.x;
    destRect.y = position.y - Game::camera.y;
}

void Tile::draw() {
    Manager::Draw(texture, &srcRect, &destRect);
    if (collider) collider->draw();
}

void Tile::destroy() {
    texture = nullptr;
}

void Tile::place(int x, int y) {
    position.x = x * Tile::SIZE;
    position.y = y * Tile::SIZE;
}
