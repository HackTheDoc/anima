#include "include/UI/UIHint.h"

#include "include/Game/Game.h"
#include "include/Game/Map/Structures/Structures.h"

#include "include/Manager.h"

UIHint::UIHint(const std::string& text, const std::string& font) {
    lbl = new UILabel(text, font, hue::black, 512);
    lbl->place(0,0);
}

UIHint::~UIHint() {}

void UIHint::place(const int x, const int y) {
    lbl->place(x - Game::camera.x, y - Game::camera.y);
}

void UIHint::place(Portal* p) {
    place(
        p->position.x + (p->collider->rect.w - lbl->width()) / 2,
        p->position.y + (p->collider->rect.h - lbl->height()) / 2
    );
}

void UIHint::place(Door* d) {
    place(
        d->position.x + (d->collider->rect.w - lbl->width()) / 2,
        d->position.y + (d->collider->rect.h - lbl->height()) / 2
    );
}

void UIHint::place(Entity* e) {
    place(
        e->position.x +(e->width / 4 - lbl->width()) / 2 ,
        e->position.y - e->height / 2
    );
}

void UIHint::place(Collider* c) {
    place(
        c->position.x + (c->rect.w - lbl->width()) / 2,
        c->position.y + (c->rect.h - lbl->height()) / 2
    );
}

void UIHint::draw() {
    lbl->draw();
}
 
void UIHint::destroy() {
    lbl->destroy();
}
