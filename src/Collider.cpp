#include "include/Game/Components/Collider.h"

#include "include/Game/Game.h"

#include "include/Manager.h"

Collider::Collider(const int w, const int h) {
    rect = {0, 0, w, h};
}

Collider::~Collider() {}

void Collider::update() {
    rect.x = position.x - Game::camera.x;
    rect.y = position.y - Game::camera.y;
}

void Collider::draw() {
    Manager::DrawRect(&rect, hue::red);
}

void Collider::place(const int x, const int y) {
    position.x = x;
    position.y = y;
}

void Collider::place(const Vector2D& pos) {
    place(pos.x, pos.y);
}
