#include "include/Game/Components/Collider.h"

#include "include/Manager.h"

#include "include/Game/Game.h"

Collider::Collider() {
    rect = {0, 0, 0, 0};
}

Collider::Collider(int w, int h) {
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

void Collider::place(int x, int y) {
    position.x = x;
    position.y = y;
}

void Collider::place(Vector2D pos) {
    place(pos.x, pos.y);
}
